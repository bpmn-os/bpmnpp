include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Catch2
FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)

FetchContent_GetProperties(catch)

if (NOT catch_POPULATED)
  FetchContent_Populate(catch)
  add_subdirectory(${catch_SOURCE_DIR} ${catch_BINARY_DIR})
endif ()

add_executable(run_tests EXCLUDE_FROM_ALL main.cpp)

target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(run_tests PRIVATE xerces-c)
target_link_libraries(run_tests PRIVATE bpmn++)

add_custom_target(
    tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tests
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
    VERBATIM
)
add_dependencies(tests run_tests)
add_dependencies(run_tests bpmn++)

