set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

##
## Check os type for binary extension.
##
if (UNIX AND NOT APPLE)
    message(STATUS              "Unix system detected.")
    set(OS_DYNAMIQUE_BIN_EXT    "")
endif (UNIX AND NOT APPLE)
if (WIN32 OR MSVC OR MSYS OR MINGW)
    message(STATUS              "Windows OS detected.")
    set(OS_DYNAMIQUE_BIN_EXT    ".exe")
endif (WIN32 OR MSVC OR MSYS OR MINGW)

set(TEST_SOURCES
    hello_world_test.cpp)

add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE 
    "${CMAKE_SOURCE_DIR}/third_party/doctest"
)

add_executable(test_runner test_runner.cpp ${TEST_SOURCES})
target_link_libraries(test_runner ${PROJECT_NAME} doctest)

add_test(all_tests test_runner)

add_custom_command( TARGET test_runner
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:test_runner> ${CMAKE_BINARY_DIR}/test/test_runner${OS_DYNAMIQUE_BIN_EXT})