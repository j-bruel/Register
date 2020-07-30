cmake_minimum_required(VERSION 3.1)
include_directories("C:\\Program Files (x86)\\cRegister\\include")
include_directories("C:\\Users\\jonat\\dev\\cRegister\\third_party\\doctest")

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
add_executable(${TESTING_PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES} ${TEST_SOURCES_FILES} ${TEST_INCLUDE_FILES})

##
## Link testing library.
##
if (WIN32 OR MSVC OR MSYS OR MINGW)
    target_link_libraries(${TESTING_PROJECT_NAME} doctest)
else()
    target_link_libraries(${TESTING_PROJECT_NAME} doctest stdc++fs)
endif (WIN32 OR MSVC OR MSYS OR MINGW)

message(${CMAKE_BINARY_DIR}/test/${TESTING_PROJECT_NAME}${OS_DYNAMIQUE_BIN_EXT})

##
## Add test.
##
add_test(NAME RUN_TESTS COMMAND ${TESTING_PROJECT_NAME})
