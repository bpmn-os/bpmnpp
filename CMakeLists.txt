cmake_minimum_required(VERSION 3.26.4)

project(bpmn++ VERSION 0.1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)

# Only when bpmn++ is built on its own, so that a consumer's choice always wins.
if(PROJECT_IS_TOP_LEVEL)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  endif()
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Optional components are built when bpmn++ is the top-level project and not when it is a dependency, so
# a consumer neither builds them nor needs their tooling, and declines nothing explicitly.
option(BPMNPP_TESTS "Build bpmn++ tests" ${PROJECT_IS_TOP_LEVEL})
option(BPMNPP_DOCS "Build bpmn++ documentation" ${PROJECT_IS_TOP_LEVEL})

if(BPMNPP_TESTS)
  add_subdirectory(tests)
endif()

# XMLObject.h uses C++23 explicit object parameters and reaches every consumer through the amalgamated
# header, so the requirement is checked here rather than downstream. A version comparison rather than a
# feature-test macro: Clang 18.1.3 compiles an explicit object parameter but does not define
# __cpp_explicit_this_parameter.
set(BPMNPP_MINIMUM_GNU_VERSION 15.2)
set(BPMNPP_MINIMUM_CLANG_VERSION 18.1.3)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS BPMNPP_MINIMUM_GNU_VERSION)
    message(FATAL_ERROR "bpmn++ requires GCC ${BPMNPP_MINIMUM_GNU_VERSION} or later, found "
                        "${CMAKE_CXX_COMPILER_VERSION}.")
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS BPMNPP_MINIMUM_CLANG_VERSION)
    message(FATAL_ERROR "bpmn++ requires Clang ${BPMNPP_MINIMUM_CLANG_VERSION} or later, found "
                        "${CMAKE_CXX_COMPILER_VERSION}.")
  endif()
else()
  message(WARNING "bpmn++ is built with GCC and Clang; ${CMAKE_CXX_COMPILER_ID} is untested.")
endif()

include(FetchContent)

# Xerces-C is declared rather than resolved from the system, so a build succeeds on a machine with nothing
# installed. It is resolved as a package rather than as a bare library so that the imported target can be
# carried as a usage requirement: bpmn++'s generated classes are built on xercesc types, so a consumer of
# the archive must link it, and no consumer should have to know that.
FetchContent_Declare(XercesC
  GIT_REPOSITORY https://github.com/apache/xerces-c.git
  GIT_TAG        v3.2.4
  FIND_PACKAGE_ARGS 3.2
)
FetchContent_MakeAvailable(XercesC)

if(TARGET XercesC::XercesC)
  set(XERCES_TARGET XercesC::XercesC)
else()
  set(XERCES_TARGET xerces-c)
endif()

# schematic++ has to be a runnable binary before this configure finishes, not merely a target: it emits
# src/xml/bpmn/CMakeLists.txt listing the sources it generates, and src/CMakeLists.txt includes that list
# while configuring. A FetchContent target would not be built until build time, which is too late, so a
# copy that cannot be resolved is configured and built here in a sub-build of its own.
set(SCHEMATICPP_VERSION 0.8.0)
# Names schematic++'s branch while its change is unmerged, which is the convention for a dependency under
# development. It becomes v${SCHEMATICPP_VERSION} when schematic++ is tagged.
set(SCHEMATICPP_REF "dependency-management")
find_package(schematicpp ${SCHEMATICPP_VERSION} QUIET)

if(SCHEMATICPP AND EXISTS ${SCHEMATICPP})
  # A parent project that already has the generator supplies it, rather than each project building its own.
  message(STATUS "bpmn++: using schematic++ supplied by the parent project at ${SCHEMATICPP}")
elseif(schematicpp_FOUND)
  get_target_property(SCHEMATICPP schematicpp::schematic++ IMPORTED_LOCATION_RELEASE)
  if(NOT SCHEMATICPP)
    get_target_property(SCHEMATICPP schematicpp::schematic++ IMPORTED_LOCATION)
  endif()
  message(STATUS "bpmn++: using an already-installed schematic++ at ${SCHEMATICPP}")
else()
  # SOURCE_SUBDIR names a directory that does not exist, so the source is populated without being added to
  # this build; it is built separately below, for the host, which is also what a cross-compiled build needs.
  FetchContent_Declare(schematicpp
    GIT_REPOSITORY https://github.com/rajgoel/schematicpp.git
    GIT_TAG        ${SCHEMATICPP_REF}
    SOURCE_SUBDIR  do-not-add-this-subdirectory
  )
  FetchContent_MakeAvailable(schematicpp)

  set(SCHEMATICPP_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/schematicpp-host)
  message(STATUS "bpmn++: building schematic++ for the host in ${SCHEMATICPP_BUILD_DIR}")

  execute_process(
    COMMAND ${CMAKE_COMMAND} -S ${schematicpp_SOURCE_DIR} -B ${SCHEMATICPP_BUILD_DIR}
            -DCMAKE_BUILD_TYPE=Release
    RESULT_VARIABLE SCHEMATICPP_CONFIGURE_RESULT
    OUTPUT_QUIET
  )
  if(NOT SCHEMATICPP_CONFIGURE_RESULT EQUAL 0)
    message(FATAL_ERROR "bpmn++: configuring schematic++ failed with ${SCHEMATICPP_CONFIGURE_RESULT}")
  endif()

  execute_process(
    COMMAND ${CMAKE_COMMAND} --build ${SCHEMATICPP_BUILD_DIR} --parallel
    RESULT_VARIABLE SCHEMATICPP_BUILD_RESULT
    OUTPUT_QUIET
  )
  if(NOT SCHEMATICPP_BUILD_RESULT EQUAL 0)
    message(FATAL_ERROR "bpmn++: building schematic++ failed with ${SCHEMATICPP_BUILD_RESULT}")
  endif()

  # schematic++ links its executable into its own source directory rather than its build directory.
  set(SCHEMATICPP ${schematicpp_SOURCE_DIR}/schematic++)
  if(NOT EXISTS ${SCHEMATICPP})
    message(FATAL_ERROR "bpmn++: schematic++ was built but is not at ${SCHEMATICPP}")
  endif()
endif()

# Internal paths, deliberately not cache variables: another project in the same build may use the same
# names, and set(... CACHE ...) does not overwrite an existing entry, so whichever configured first would
# decide both. The engine declares SOURCE_DIR and XML_DIR too.
set(LIB_DIR "lib")
set(INCLUDE_DIR "include")
message("-- Library will be created in folder: ${LIB_DIR}")

# Set folder in which sources are located
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

# The generated XML classes are build output and belong in the build tree, not in the checkout.
set(XML_DIR "${CMAKE_CURRENT_BINARY_DIR}/xml")

# Build output goes to the build tree, so that a consumer building bpmn++ writes nothing into this
# checkout and two build directories do not overwrite each other's archive.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${LIB_DIR})

# ccache is chosen by whoever is building, not imposed by a dependency: a global property set here would
# govern a consumer's targets too. As a dependency bpmn++ sets nothing.
if (PROJECT_IS_TOP_LEVEL)
  find_program(CCACHE_FOUND "ccache")
  set(CCACHE_SUPPORT ON CACHE BOOL "Enable ccache support")
  if (CCACHE_FOUND AND CCACHE_SUPPORT)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_FOUND}")
  elseif (CCACHE_SUPPORT)
    message(WARNING
      "ccache not found. Re-compilation can be unnecessarily slow. "
      "To install run: sudo apt install ccache")
  endif()
endif()

set(SCHEMATICPP_DIR ${CMAKE_CURRENT_BINARY_DIR}/schematicpp)
set(SCHEMATICPP_OUTPUT_DIR ${SCHEMATICPP_DIR}/xml)

# The XML classes are regenerated on every configure rather than once, so that editing a schema takes
# effect. Guarding this on the directory's existence left a stale copy in place for ever.
set(BPMNPP_SCHEMAS xsd/DC.xsd xsd/DI.xsd xsd/BPMNDI.xsd xsd/Semantic.xsd xsd/BPMN20.xsd)

message("-- Create XML classes in: ${XML_DIR}")
file(MAKE_DIRECTORY ${XML_DIR})
execute_process(
  COMMAND ${SCHEMATICPP} -n bpmn -o ${XML_DIR} -i ${BPMNPP_SCHEMAS}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  RESULT_VARIABLE BPMNPP_GENERATE_RESULT
  OUTPUT_QUIET
)
if(NOT BPMNPP_GENERATE_RESULT EQUAL 0)
  message(FATAL_ERROR "bpmn++: schematic++ failed with ${BPMNPP_GENERATE_RESULT}")
endif()

# Editing a schema forces a reconfigure, which is what regenerates the classes. Generation cannot be a
# build rule, because the list of sources it produces is read while configuring.
foreach(schema IN LISTS BPMNPP_SCHEMAS)
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${schema})
endforeach()

# Generate the single header file
set(SINGLE_HEADER_PATH "${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}/${PROJECT_NAME}.h")
message("-- Header location: ${SINGLE_HEADER_PATH}")

message("-- Create single header file")

# Create output directory for the library
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR})

# Get lists of all headers and sources
# src/CMakeLists.txt resolves both sets itself: the generated ones against XML_DIR in the build tree and
# the hand-written ones against SOURCE_DIR, which no longer share a prefix.
include("${SOURCE_DIR}/CMakeLists.txt")

# Generate the single header file
file(WRITE "${SINGLE_HEADER_PATH}" "// Automatically generated single header file\n")

foreach(HEADER ${bpmn_HEADERS})
  file(READ ${HEADER} HEADER_CONTENTS)
  string(REGEX REPLACE "#include \"[^\"]*\"\n" "" HEADER_CONTENTS "${HEADER_CONTENTS}")
  file(APPEND "${SINGLE_HEADER_PATH}" "${HEADER_CONTENTS}")
endforeach()

# Generate the documentation
if (BPMNPP_DOCS)
  find_program(DOXYGEN_FOUND "doxygen")
  find_program(DOT_FOUND "dot")
  if (NOT DOXYGEN_FOUND OR NOT DOT_FOUND)
    # An absent renderer disables the documentation rather than the whole configure step.
    message(WARNING "doxygen or graphviz not found; no docs target. "
                    "To install run: sudo apt install doxygen graphviz")
    set(BPMNPP_DOCS OFF)
  endif()
endif()

if (BPMNPP_DOCS)
  include(ExternalProject)

  ExternalProject_Add(doxygen-awesome
        GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
        GIT_TAG v2.3.1
        SOURCE_DIR ${CMAKE_BINARY_DIR}/doxygen-awesome
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        CONFIGURE_COMMAND ""
  )

  # Add Doxygen target
  add_custom_target(docs
    COMMAND bash -c "sed -i 's|https://github.com/jothepro/doxygen-awesome-css|https://github.com/bpmn-os/bpmnpp|g' ${CMAKE_BINARY_DIR}/doxygen-awesome/doxygen-custom/header.html"
    COMMAND bash -c "echo '</body></html>' > ${CMAKE_BINARY_DIR}/doxygen-awesome/doxygen-custom/footer.html"
    COMMAND ${CMAKE_COMMAND} -E env
            "DOXYGEN_AWESOME_DIR=${CMAKE_BINARY_DIR}/doxygen-awesome"
            "DOXYGEN_OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/docs"
            "DOXYGEN_XML_DIR=${XML_DIR}"
            doxygen ${PROJECT_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating Doxygen documentation (this may take a while)"
    VERBATIM
    DEPENDS doxygen-awesome
  )
endif()

add_library(${PROJECT_NAME} STATIC ${bpmn_SOURCES})

# A consumer names the same target whether bpmn++ was built in its tree or resolved from a prefix.
add_library(bpmnpp::bpmn++ ALIAS ${PROJECT_NAME})

# Usage requirements. A consumer includes <bpmn++.h> and links Xerces-C without stating either: the
# amalgamated header's directory and the Xerces dependency travel with the target.
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    # The hand-written sources include the generated classes as "xml/bpmn/...", a path that used to be
    # relative to src/. Now that they are generated into the build tree, that root is what resolves it.
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC XercesC::XercesC)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Delete xml directory when running `make clean`
set_property(
  TARGET ${PROJECT_NAME}
  APPEND
  PROPERTY ADDITIONAL_CLEAN_FILES "${XML_DIR}"
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
  -O3
  -Werror
  -pedantic-errors
  -Wpedantic
  -Wall
  -Wextra
  -Wconversion
  -Wsign-conversion
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Only a release build is installable. A debug archive installed into a prefix would poison every consumer
# that linked it, and nothing in the installed package records how it was built. This runs before any other
# install rule, so the attempt stops rather than half-completing.
install(CODE "
  if(NOT \"${CMAKE_BUILD_TYPE}\" STREQUAL \"Release\")
    message(FATAL_ERROR \"bpmn++: only a release build can be installed; this is a ${CMAKE_BUILD_TYPE} build.\")
  endif()
")

# Install the header files
install(FILES ${SINGLE_HEADER_PATH} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the library, exported so that a consumer imports a target carrying its usage requirements
# rather than reconstructing an include path and a link line.
install(TARGETS ${PROJECT_NAME}
  EXPORT  bpmnpp-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT bpmnpp-targets
  FILE      bpmnpp-targets.cmake
  NAMESPACE bpmnpp::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bpmnpp
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/bpmnppConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/bpmnppConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bpmnpp
)

# bpmn++ is at 0.1.0, below 1.0.0, so compatibility is SameMinorVersion: a consumer requiring 0.1.0
# accepts any later 0.1.x and refuses 0.2.0.
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/bpmnppConfigVersion.cmake
  VERSION       ${PROJECT_VERSION}
  COMPATIBILITY SameMinorVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/bpmnppConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/bpmnppConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bpmnpp
)

