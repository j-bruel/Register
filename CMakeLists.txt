##
## Cmake minimun version
##
cmake_minimum_required(VERSION 3.13)

##
## Projet Name
##
project(cRegister)

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 11)

##
## Library location
##
if (UNIX AND NOT APPLE)
    message(STATUS "Unix system detected.")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif (UNIX AND NOT APPLE)
if (WIN32 OR MSVC OR MSYS OR MINGW)
    message(STATUS "Windows OS detected.")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif (WIN32 OR MSVC OR MSYS OR MINGW)

##
## Flags
##
if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags.")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -W -Wall -Wextra -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -g3")
endif (CMAKE_COMPILER_IS_GNUCXX)

##
## Headers and library included
##
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES         ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Package
##
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
