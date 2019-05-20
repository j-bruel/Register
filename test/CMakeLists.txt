##
## Set testing project name.
##
set(TESTING_PROJECT_NAME test_runner)

##
## Initialize current binary output directory.
##
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

##
## Sources files
##
file(GLOB_RECURSE TEST_SOURCES_FILES    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_INCLUDE_FILES    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Add testing library (libary & header).
##
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE "${CMAKE_SOURCE_DIR}/third_party/doctest")

##
## Generate executable file.
##
add_executable(${TESTING_PROJECT_NAME} ${TEST_SOURCES_FILES} ${TEST_INCLUDE_FILES})

##
## Link testing library.
##
if (WIN32 OR MSVC OR MSYS OR MINGW)
    target_link_libraries(${TESTING_PROJECT_NAME} ${PROJECT_NAME} doctest)
else()
    target_link_libraries(${TESTING_PROJECT_NAME} ${PROJECT_NAME} doctest stdc++fs)
endif (WIN32 OR MSVC OR MSYS OR MINGW)

##
## Add test.
##
add_test(all_tests ${TESTING_PROJECT_NAME})

##
## Copy test file to building directory for auto-testing scripts.
##
add_custom_command( TARGET ${TESTING_PROJECT_NAME}
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TESTING_PROJECT_NAME}> ${CMAKE_BINARY_DIR}/test/${TESTING_PROJECT_NAME}${OS_DYNAMIQUE_BIN_EXT})