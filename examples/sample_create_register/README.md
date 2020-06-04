# cRegister: Example - Create a single register

## Overview

This is a basic usage of the cRegister API.

## Features

This example create a simple register and wait few seconds.
The register will not be destroy.

This example is usefull to test if the installation is complete and copy the CMakeLists.txt file for a new project.

## Usage

### Platforms

This cRegister API example is available on :

* `Linux`
* `MacOS`
* `Windows`

### Requirements

This example is designed to have fairly minimal requirements to build, but there are some.
In addition, the library is built in `c++17`.
These are the base requirements to build and run this example from a source package (as described below):

#### Building library

##### Windows Requirements

* `CMake` At least v3.1
* Windows `command prompt`
* Microsoft `Visual C++ 2015`
* `cRegister` API installed

##### Linux & MacOS Requirements

* GNU-compatible `CMake` and `Make` (at least v3.1).
* POSIX-standard `shell`.
* A `C++17`-standard-compliant compiler
* `cRegister` API installed

### Build and install

#### Variables

| Variable           | Description                                                                                    | Possible Values                                 | Default Value |
|--------------------|------------------------------------------------------------------------------------------------|-------------------------------------------------|---------------|
| `CMAKE_BUILD_TYPE` | Specifies what build type (configuration) will be built in this build tree.                    | `Debug`/`Release`/`RelWithDebInfo`/`MinSizeRel` | `Release`     |

#### Targets

| Target           | Description              |
|------------------|--------------------------|
| `[Nothing]`      | Build the application.   |
| `clean`          | Clean all built targets. |

#### Windows

* `mkdir build` _In the root project directory_
* `cd build`
* `cmake ..`
* `cmake --build .`

#### Linux & MacOS

To build the library on linux or MacOS :

* `mkdir build` _In the root project directory_
* `cd build`
* `cmake ..`
* `make`

This will generate a executable `sample_create_register[.exe]` into the `bin` directory.
