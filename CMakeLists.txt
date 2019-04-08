##
## Cmake minimun version
##
cmake_minimum_required(VERSION 3.13)

##
## Projet version
##
set(PROJECT_VERSION 1.0)

##
## Projet Name
##
project(cRegister
        VERSION ${PROJECT_VERSION})

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 11)

##
## Library location and configuration
##
if (UNIX AND NOT APPLE)
    message(STATUS "Unix system detected.")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif (UNIX AND NOT APPLE)
if (WIN32 OR MSVC OR MSYS OR MINGW)
    message(STATUS "Windows OS detected.")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_DEBUG_POSTFIX "d")
endif (WIN32 OR MSVC OR MSYS OR MINGW)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

##
## Flags
##
if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags.")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -W -Wall -Wextra -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -g3")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${CMAKE_CXX_FLAGS_DEBUG}>")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${CMAKE_CXX_FLAGS_RELEASE}>")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT) # Set the DLLEXPORT variable to export symbols
endif ()

##
## Headers and library included
##
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

##
## Package
##
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

##
## Set project name with version.
##
set_target_properties(  ${PROJECT_NAME}
                            PROPERTIES
                                VERSION ${PROJECT_VERSION}
                                SOVERSION ${PROJECT_VERSION}
)