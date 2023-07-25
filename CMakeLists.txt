cmake_minimum_required(VERSION 3.26.4)

project(bpmn++)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)

# Check dependencies
find_library(XERCES_LIB xerces-c)
if(NOT XERCES_LIB)
  message(FATAL_ERROR "xerces-c library not found.\nTo install run: sudo apt install libxerces-c-dev")
endif()

find_program(SCHEMATICPP schematic++)
if(NOT SCHEMATICPP)
  message(FATAL_ERROR "schematic++ not found.\nDownload schematic++ from: https://github.com/rajgoel/schematicpp")
endif()

# Set folder for the library to be created
set(LIB_DIR "lib" CACHE STRING "Library directory")
message("-- Library will be created in folder: ${LIB_DIR}")

# Set folder in which sources are located
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src" CACHE STRING "Source directory")
set(XML_DIR "${SOURCE_DIR}/xml" CACHE STRING "XML classes source directory")

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${LIB_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_program(CCACHE_FOUND "ccache")
set(CCACHE_SUPPORT ON CACHE BOOL "Enable ccache support")
if (CCACHE_FOUND AND CCACHE_SUPPORT)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "ccache")
endif()

set(SCHEMATICPP_DIR ${CMAKE_CURRENT_BINARY_DIR}/schematicpp)
set(SCHEMATICPP_OUTPUT_DIR ${SCHEMATICPP_DIR}/xml)

if(NOT EXISTS "${XML_DIR}")
  message("-- Create XML classes in: ${XML_DIR}")
  file(MAKE_DIRECTORY ${XML_DIR})
  # Generate XML classes and headers
  execute_process(
    COMMAND ${SCHEMATICPP} -n bpmn -o ${XML_DIR} -i xsd/DC.xsd xsd/DI.xsd xsd/BPMNDI.xsd xsd/Semantic.xsd xsd/BPMN20.xsd
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

# Generate the single header file
set(SINGLE_HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}/${CMAKE_PROJECT_NAME}.h")
message("-- Header location: ${SINGLE_HEADER_PATH}")

message("-- Create single header file")

# Create output directory for the library
file(MAKE_DIRECTORY ${LIB_DIR})

# Get lists of all headers and sources
include("${SOURCE_DIR}/CMakeLists.txt")
list(TRANSFORM bpmn_HEADERS PREPEND "${SOURCE_DIR}/")
list(TRANSFORM bpmn_SOURCES PREPEND "${SOURCE_DIR}/")

# Generate the single header file
file(WRITE "${SINGLE_HEADER_PATH}" "// Automatically generated single header file\n")

foreach(HEADER ${bpmn_HEADERS})
  file(READ ${HEADER} HEADER_CONTENTS)
  string(REGEX REPLACE "#include \"[^\"]*\"\n" "" HEADER_CONTENTS "${HEADER_CONTENTS}")
  file(APPEND "${SINGLE_HEADER_PATH}" "${HEADER_CONTENTS}")
endforeach()

# Generate the documentation
find_program(DOXYGEN_FOUND "doxygen")
set(DOCUMENTATION ON CACHE BOOL "Create documentation")
if (DOXYGEN_FOUND AND DOCUMENTATION)
  # Add Doxygen target
  add_custom_target(docs
    COMMAND doxygen ${PROJECT_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating Doxygen documentation (this may take a while)"
    VERBATIM
  )
endif()

add_library(${CMAKE_PROJECT_NAME} STATIC ${bpmn_SOURCES})

# Delete xml directory when running `make clean`
set_property(
  TARGET ${PROJECT_NAME}
  APPEND
  PROPERTY ADDITIONAL_CLEAN_FILES "${XML_DIR}"
)

target_compile_options(${CMAKE_PROJECT_NAME}
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

# Install the header files
install(FILES ${SINGLE_HEADER_PATH} DESTINATION include)

# Install the library
install(TARGETS ${CMAKE_PROJECT_NAME} ARCHIVE DESTINATION lib)

