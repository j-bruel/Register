# Requirements, Build & Install {#requirement_build_install}

\tableofcontents

cRegister library is designed to have fairly minimal requirements to build and use with your projects, but there are some.
In addition, the library is build in c++14.

These are the base requirements to build and use cRegister library from a source package.

\section requirement Project Requirement

The requirement depend on the OS target.

To build the cRegister library only : 

**Build library**

_Windows_

* `CMake` At least v3.1
* Windows `command prompt`
* Microsoft `Visual C++ 2015`

_Linux & MacOS_

* GNU-compatible `CMake` and `Make` (at least v3.1).
* POSIX-standard `shell`.
* A `C++14`-standard-compliant compiler

**Build documentation**

- `Doxygen`

**Build test**

To be more efficience, cRegister library is delivered with a set of tests.
You should build and run thoses run after install for testing installation purpose.

- `gcov`
- `lcov`

\section build How to build & install

**Windows**

* `mkdir build` **_## In the root project directory_**
* `cd build`
* `cmake .. -DBUILD_TESTS=<ON|OFF> -DGEN_DOCS=<ON|OFF> -DENABLE_COVERAGE=<ON|OFF>`
* `cmake --build .`

Launching test or coverage (after build) : 

* `cmake --build . --target RUN_TESTS`
* `cmake --build . --target coverage`

Installing the library :

* `cmake --build . --target install`

Launch documentation building :

* `cmake --build . --target doc`

**Linux & MacOS**

To build the library on linux or MacOS :

* `mkdir build` **_## In the root project directory_**
* `cd build`
* `cmake .. -DBUILD_TESTS=<ON|OFF> -DGEN_DOCS=<ON|OFF> -DENABLE_COVERAGE=<ON|OFF>`
* `make`

Launching test or coverage (after build) : 

* `make test`
* `make coverage`

Installing the library :

* `make install`

Launch documentation building :

* `make doc`

This will generate a shared library `[lib]cRegister.[so][dll]` and a testing application `cRegister[.exe]`.
