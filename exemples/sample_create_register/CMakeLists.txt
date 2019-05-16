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
set(CMAKE_CXX_STANDARD 14)

##
## Binary location
##
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_CURRENT_SOURCE_DIR}/bin)

##
## Flags
##
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    ##
    ## Set Linux compilation flag.
    ##
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS} -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    ##
    ## Set Windows compilation flag.
    ##
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")


##
## Check os type for library extension.
##
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS              "Unix system detected.")
    set(OS_DYNAMIQUE_LIB_EXT    "so")
endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
if (WIN32 OR MSVC OR MSYS OR MINGW)
    message(STATUS              "Windows OS detected.")
    set(OS_DYNAMIQUE_LIB_EXT    "lib")
endif (WIN32 OR MSVC OR MSYS OR MINGW)

##
## Cmake variables (options).
##
option(REGISTER_LIBS_DIR    "Register library directory." $ENV{REGISTER_LIBS_DIR})
option(REGISTER_HEADERS_DIR "Register headers directory." $ENV{REGISTER_HEADERS_DIR})

##
## Give message from variables setting
##
if (REGISTER_LIBS_DIR)
    message(STATUS  "The Register library directory (REGISTER_LIBS_DIR) is " ${REGISTER_LIBS_DIR})
else()
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS  "The register library directory (REGISTER_LIBS_DIR) is undefine.")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (WIN32 OR MSVC OR MSYS OR MINGW)
        message(FATAL_ERROR "The register library directory (REGISTER_LIBS_DIR) is undefine. This variable must be define in cmake argument or in the environment.")
    endif (WIN32 OR MSVC OR MSYS OR MINGW)
endif()
if (REGISTER_HEADERS_DIR)
    message(STATUS  "The Register headers directory (REGISTER_HEADERS_DIR) is " ${REGISTER_HEADERS_DIR})
else()
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS  "The register headers directory (REGISTER_HEADERS_DIR) is undefine.")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (WIN32 OR MSVC OR MSYS OR MINGW)
        message(FATAL_ERROR "The register headers directory (REGISTER_HEADERS_DIR) is undefine. This variable must be define in cmake argument or in the environment.")
    endif (WIN32 OR MSVC OR MSYS OR MINGW)

endif()

##
## Headers and library included
##
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
if (REGISTER_HEADERS_DIR)
    include_directories(${REGISTER_HEADERS_DIR})
endif(REGISTER_HEADERS_DIR)

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES         ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Package
##
add_executable(${PROJECT_NAME}          ${SOURCE_FILES} ${INCLUDE_FILES})

if (REGISTER_LIBS_DIR)
    target_link_libraries(${PROJECT_NAME}   ${REGISTER_LIBS_DIR}/cRegister.${OS_DYNAMIQUE_LIB_EXT})
else()
    target_link_libraries(${PROJECT_NAME}   cRegister.${OS_DYNAMIQUE_LIB_EXT})
endif(REGISTER_LIBS_DIR)