##
## Cmake minimun version
##
cmake_minimum_required(VERSION 3.1)

##
## Project version.
##
set(cRegister_VERSION_MAJOR 0)
set(cRegister_VERSION_MINOR 1)
set(cRegister_VERSION_PATCH 0)
set(cRegister_VERSION "${cRegister_VERSION_MAJOR}.${cRegister_VERSION_MINOR}.${cRegister_VERSION_PATCH}")

##
## Project description.
##
set(PROJECT_DESCRIPTION "\"Register C++ API. Smart memory, allowing to interact and persist data in an architectural, dynamic and simplified way.\"")

##
## Projet Name
##
project(cRegister VERSION ${cRegister_VERSION} DESCRIPTION ${PROJECT_DESCRIPTION})

##
## Project name, use for Doxygen.
##
set(PROJ_NAME "\"${PROJECT_NAME}\"")

##
## Set configuration file.
##
configure_file(include/jbr/config.hpp.in
               ${CMAKE_BINARY_DIR}/include/jbr/config.hpp)

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

##
## Set output directories.
##
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/lib)

##
## Building options : Tests, documentation & coverage. All options are activate by default.
##
option(BUILD_TESTS "Build test executable" OFF)
option(GEN_DOCS "Generate documentation" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

##
## Set cmake modules path.
##
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

##
## Windows shared libraries building mandatory.
##
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

##
## Always include the source and build directories in the include path.
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)

##
## Cmake build configuration options.
##
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as no build type was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type (Debug/Release)" FORCE)
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
        setup_target_for_coverage(NAME coverage EXECUTABLE ctest DEPENDENCIES coverage)
else (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        ##
        ## Set Linux compilation flag.
        ##
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        ##
        ## Set Windows compilation flag.
        ##
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
        ##
        ## Export no symbols by default (if the compiler supports it).
        ## This makes e.g. GCC's "visibility behavior" consistent with MSVC's.
        ## On Windows/MSVC this is a noop.
        ##
        set(CMAKE_C_VISIBILITY_PRESET hidden)
        set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Generation static library.
##
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})

##
## Remove library prefix and add version to library.
##
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${cRegister_VERSION})

##
## Library linkage with headers.
##
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

##
## Check os type to copy libraries on windows case.
##
if (WIN32 OR MSVC OR MSYS OR MINGW)
    message(STATUS              "Windows OS detected, copying libraries files.")
    add_custom_command( TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/test/${PROJECT_NAME}.dll)
endif (WIN32 OR MSVC OR MSYS OR MINGW)

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
## Install the built library into the appropriate directory.
##
install(TARGETS ${PROJECT_NAME}
                ARCHIVE DESTINATION lib
                LIBRARY DESTINATION lib
                RUNTIME DESTINATION bin)

##
## Install the project header files into the appropriate directory.
##
install(DIRECTORY include/ DESTINATION include PATTERN "config.hpp.in" EXCLUDE) # Install our main header files
install(FILES ${CMAKE_BINARY_DIR}/include/jbr/config.hpp DESTINATION include/jbr) # Install our configuration file

##
## Install the project's extra files
##
install(FILES README.md LICENSE DESTINATION share/jbr/reg)
