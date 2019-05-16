# cRegister

[![Build Status](https://travis-ci.org/j-bruel/cRegister.svg?branch=develop)](https://travis-ci.org/j-bruel/cRegister)
[![Build status](https://ci.appveyor.com/api/projects/status/yu3pueottceo7711?svg=true)](https://ci.appveyor.com/project/j-bruel/cregister)
[![codecov](https://codecov.io/gh/j-bruel/cRegister/branch/develop/graph/badge.svg)](https://codecov.io/gh/j-bruel/cRegister)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c1027b37f11442529e84810a6fed5aa3)](https://www.codacy.com/app/j-bruel/cRegister?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=j-bruel/cRegister&amp;utm_campaign=Badge_Grade)
[![Documentation](https://codedocs.xyz/j-bruel/cRegister.svg)](https://codedocs.xyz/j-bruel/cRegister/)
[![Open Source Love](https://badges.frapsoft.com/os/mit/mit.svg?v=102)](https://github.com/j-bruel/cRegister/blob/master/LICENSE)

## Overview

Modern cross platforms C++ API for cRegisters. Register are smart memory, data manager, allowing to interact and persist data in an architectural, dynamic and simplified way.

## What is a Register

### Philosophy

### How does it work

## Features

## Usage

### Platforms

cRegister API platforms available :

* `Linux`
* `MacOS`
* `Windows`

### Requirements

The following tools must be preinstalled before using this project.

#### Buidling

- `CMake` At least v3.1
- `g++` At least c++ 14
- `Visual compiler`

#### Documentation

- `Doxygen`

#### Testing

- `gcov`
- `lcov`

### Build and install

#### Variables

| Variable           | Description                                                                                    | Possible Values                                 | Default Value |
|--------------------|------------------------------------------------------------------------------------------------|-------------------------------------------------|---------------|
| `CMAKE_BUILD_TYPE` | On a single configuration generator, this string determines the build type of the application. | `Debug`/`Release`/`RelWithDebInfo`/`MinSizeRel` | `Release`     |
| `GEN_DOCS`         | An option used to determine if documentation will or will not be generated.                    | `ON`/`OFF`                                      | `ON`          |
| `BUILD_TESTS`      | An option used to determine if the test executable should or should not be built.              | `ON`/`OFF`                                      | `ON`          |
| `ENABLE_COVERAGE`  | An option used to determine whether coverage should be enabled or not                          | `ON`/`OFF`                                      | `ON`          |

#### Targets

| Target           | Description                                                    |
|------------------|----------------------------------------------------------------|
| `[Nothing]`      | Build the application (Including `test` if `BUILD_TESTS=ON`).  |
| `install`        | Install all built targets.                                     |
| `test`           | If tests were built, then run all tests.                       |
| `doc`            | If `GEN_DOCS=ON`, then generate documentation using `Doxygen`. |
| `coverage`       | If `ENABLE_COVERAGE=ON`, then generate code coverage.          |
| `clean`          | Clean all built targets.                                       |

#### Windows

#### Linux & MacOS

* `cmake .. -DBUILD_TESTS=<ON|OFF> -DGEN_DOCS=<ON|OFF> -DENABLE_COVERAGE=<ON|OFF>`
* `make`
* `make install`

### Building with

### Example

## Contributing

cRegister project is developed on GitHub at [cRegister](https://github.com/j-bruel/cRegister).
To report an issue or send a pull request, use the [issue tracker](https://github.com/j-bruel/cRegister/issues).

## License

This software is distributed under [MIT license](http://www.opensource.org/licenses/mit-license.php), so feel free to integrate it in your commercial products.
