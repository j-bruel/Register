##
## Cmake minimun version
##
cmake_minimum_required(VERSION 3.1)

##
## Projet Name
##
project(cRegister)

##
## Project version.
##
set(cRegister_VERSION_MAJOR 1)
set(cRegister_VERSION_MINOR 0)
set(cRegister_VERSION_PATCH 0)
set(cRegister_VERSION "${cRegister_VERSION_MAJOR}.${cRegister_VERSION_MINOR}.${cRegister_VERSION_PATCH}")

##
## Project name, use for Doxygen.
##
set(PROJ_NAME "\"${PROJECT_NAME}\"")

##
## Project description.
##
set(PROJECT_DESCRIPTION "\"Register C++ API. Smart memory, allowing to interact and persist data in an architectural, dynamic and simplified way.\"")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/project-abbr/config.hpp.in
               ${CMAKE_BINARY_DIR}/include/project-abbr/config.hpp)

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

##
## Building options : Tests, documentation & coverage. All options are activate by default.
##
option(BUILD_TESTS "Build test executable" ON)
option(GEN_DOCS "Generate documentation" ON)
option(ENABLE_COVERAGE "Enable code coverage" ON)

##
## Set cmake modules path.
##
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

##
## Cmake build configuration options.
##
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as no build type was specified.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type (Debug/Release)" FORCE)
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

##
## Enable coverage generation if option is set to ON.
##
if (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
        if (NOT BUILD_TESTS)
            message(FATAL_ERROR "Tests must be enabled for code coverage!")
        endif (NOT BUILD_TESTS)
        include(CodeCoverage)
        append_coverage_compiler_flags()
        set(COVERAGE_EXCLUDES "/usr/include/\\*;${CMAKE_SOURCE_DIR}/src/main.cpp;${CMAKE_SOURCE_DIR}/test/*;${CMAKE_SOURCE_DIR}/third_party/doctest/*")
        setup_target_for_coverage(NAME coverage EXECUTABLE ctest DEPENDENCIES coverage)
else (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    ##
    ## Set Linux compilation flag.
    ##
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
    ##
    ## Set Windows compilation flag.
    ##
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)

##
## Temporary library sources, will be replace by SOURCE_FILES when binary generation will be remove for only library.
##
set(LIBRARY_SOURCES
    src/factorial.cpp
    src/hello_world.cpp
)

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Generation static library.
##
add_library(${PROJECT_NAME}-lib ${LIBRARY_SOURCES})
##
## Remove library prefix.
##
set_target_properties(${PROJECT_NAME}-lib PROPERTIES PREFIX "")
##
## Library linkage.
##
target_include_directories(${PROJECT_NAME}-lib PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

##
## Generation application.
##
add_executable(${PROJECT_NAME}          src/main.cpp)
##
## Linkin the library with the application.
##
target_link_libraries(${PROJECT_NAME}   ${PROJECT_NAME}-lib)

##
## Build test settings.
##
if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif (BUILD_TESTS)

##
## Build documentation settings.
##
if (GEN_DOCS)
    add_subdirectory(./doc)
endif (GEN_DOCS)

##
## Install the built library and executable into the appropriate directory
##
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(TARGETS ${PROJECT_NAME}-lib
                ARCHIVE DESTINATION lib
                LIBRARY DESTINATION lib
                RUNTIME DESTINATION bin)

##
## Install the project header files into the appropriate directory.
##
install(DIRECTORY include/ DESTINATION include PATTERN "config.hpp.in" EXCLUDE) # Install our main header files
install(FILES ${CMAKE_BINARY_DIR}/include/project-abbr/config.hpp DESTINATION include/project-abbr) # Install our configuration file

##
## Install the project's extra files
##
install(FILES README.md LICENSE DESTINATION share/project-abbr)
