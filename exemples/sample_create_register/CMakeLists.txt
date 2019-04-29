##
## Cmake minimun version
##
cmake_minimum_required(VERSION 3.13)

##
## Projet Name
##
project(sample_create_register)

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 11)

##
## Binary location
##
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_CURRENT_SOURCE_DIR}/bin)

##
## Flags
##
if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS              "GCC detected, adding compile flags.")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -W -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_RELEASE} -g3")
endif (CMAKE_COMPILER_IS_GNUCXX)

##
## Check os type for library extension.
##
if (UNIX AND NOT APPLE)
    message(STATUS              "Unix system detected.")
    set(OS_DYNAMIQUE_LIB_EXT    "so")
endif (UNIX AND NOT APPLE)
if (WIN32 OR MSVC OR MSYS OR MINGW)
    message(STATUS              "Windows OS detected.")
    set(OS_DYNAMIQUE_LIB_EXT    "lib")
endif (WIN32 OR MSVC OR MSYS OR MINGW)

##
## Cmake variables
##
set(REGISTER_LIBS_DIR       "$ENV{REGISTER_LIBS_DIR}")
set(REGISTER_HEADERS_DIR    "$ENV{REGISTER_HEADERS_DIR}")

##
## Give message from variables setting
##
if (REGISTER_LIBS_DIR)
    message(STATUS              "The Register library directory (REGISTER_LIBS_DIR) is " ${REGISTER_LIBS_DIR})
else()
    message(STATUS              "The Register library directory (REGISTER_LIBS_DIR) is undefine in the environment.")
    set(REGISTER_LIBS_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/")
    message(STATUS              "Default Register library directory path is use : " ${REGISTER_LIBS_DIR})
endif()
if (REGISTER_HEADERS_DIR)
    message(STATUS              "The Register headers directory (REGISTER_HEADERS_DIR) is " ${REGISTER_HEADERS_DIR})
else()
    message(STATUS              "The Register headers directory (REGISTER_HEADERS_DIR) is undefine in the environment.")
    set(REGISTER_HEADERS_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/")
    message(STATUS              "Default Register headers directory path is use : " ${REGISTER_HEADERS_DIR})
endif()

##
## Headers and library included
##
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${REGISTER_HEADERS_DIR})

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES         ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Package
##
add_executable(${PROJECT_NAME}          ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME}   ${REGISTER_LIBS_DIR}/cRegister.${OS_DYNAMIQUE_LIB_EXT})