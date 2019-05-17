# Directory Structure {#directory_structure}

Ignoring all extraneous files, this is the structure that this project uses: 

    cRegister/
    ├── CMakeLists.txt
    ├── bin/
    ├── cmake/
    │   └── Modules/
    │       └── CodeCoverage.cmake
    ├── doc/
    │   ├── CMakeLists.txt
    │   ├── Doxyfile.in
    │   ├── directory_structure.md
    │   ├── main_page.md
    │   └── ...
    ├── exemples
    │   └── sample_create_register/
    ├── include/
    │   └── cRegister/
    │       ├── config.hpp.in
    │       └── HelloWorld.hpp
    ├── lib/
    ├── src/
    │   ├── HelloWorld.cpp
    │   └── main.cpp
    ├── test/
    │   ├── CMakeLists.txt
    │   ├── include
    │   └── src
    │       ├── hello_world_test.cpp
    │       └── test_runner.cpp
    └── third_party/
        └── doctest/
            └── doctest.h

This may all look very complex, but here is an explanation of all of the directories:

| Directory     | Purpose                                                                                                                        |
|---------------|--------------------------------------------------------------------------------------------------------------------------------|
| `bin`         | Contains all binaries generate by the cRegister building. Only testing binary for now.                                         |
| `cmake`       | Contains all CMake related configuration files.                                                                                |
| `doc`         | Contains Doxygen configuration files, which can be used to create documentation for the project using the CMake target `doc`.  |
| `exemples`    | Contains all usages library project.                                                                                           |
| `include`     | Contains all the project public include files, namespaced in a directory which is an abbreviation of the project name.         |
| `lib`         | Contains all libraries generate bu the cRegister building.                                                                     |
| `src`         | Contains the implementations of all files in `include`. Private level includes and implementations are also in this directory. |
| `test`        | Contains test files to unit test the library portion of the application.                                                       |
| `third_party` | Contains CMake configuration files for third party dependencies or single header files for projects with single includes.      |
