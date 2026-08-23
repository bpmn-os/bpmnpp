# bpmn++

## A BPMN parser library, written in C++.

This library provides a parser library for BPMN 2.0 allowing easy access to all elements and children (no getters or setters).

- **Download:** https://github.com/bpmn-os/bpmnpp
- **Documentation:** https://bpmn-os.github.io/bpmnpp

## Requirements

A C++23 compiler, GCC 15.2 or Clang 18.1.3 or later, CMake 3.26.4 or later, and git.

Xerces-C++ 3.2.x, schematic++ and Catch2 are fetched automatically unless they are installed already.

## Build

This project has two preset configurations that are created in folders `build/release` and `build/debug`. Presets are configured the first time they are needed or when running `make configure`.

| Preset | Folder | Compiled with | Used for |
| --- | --- | --- | --- |
| `release` | `build/release` | `-O3 -DNDEBUG`, assertions off | building, documentation, installing |
| `debug` | `build/debug` | `-O3 -g`, assertions live | development, tests |

You can build the single header and the library by

```sh
make # (release)
```
or
```sh
make dev # (debug)
```
with the preset indicated in parentheses. This creates `build/release/include/bpmn++.h` and
`build/release/lib/libbpmn++.a`, respectively the same two files under `build/debug`.

## Tests

To (build and) run the test suite, use
```sh
make tests # (debug)
```

Once the tests are built (and run) with `make tests`, selected tests carrying a given Catch2 tag can be run
with
```sh
cd tests && ../build/debug/tests/run_tests "[selected_tag]"
```
The test binary reads `diagram.bpmn` by a relative path, so it is run from the `tests` folder.

## Documentation

To generate docs in `build/release/docs/html` folder, run

```sh
make docs # (release)
```

> [!NOTE]
> Building the documentation requires `doxygen` and `graphviz`. Run `sudo apt install doxygen graphviz` to install these.

## Installation

To install, run
```sh
make # (release)
sudo make install
```
to copy
```
include/bpmn++.h
lib/libbpmn++.a
lib/cmake/bpmnpp/
```
into `/usr/local`.

Alternatively, run
```sh
cmake --install build/release --prefix <target>
```
to install these files into the `<target>` folder.

> [!NOTE]
> Only a release build can be installed. Installing `build/debug` is refused with an error.

A consumer can resolve the library with

```cmake
find_package(bpmnpp REQUIRED)
target_link_libraries(mytarget PRIVATE bpmnpp::bpmn++)
```

Nothing further is needed when bpmn++ was installed into `/usr/local`. For a custom target folder, add
`-DCMAKE_PREFIX_PATH=<target>` when configuring the consumer.

A minimum version can be required, for instance `find_package(bpmnpp 0.1.0 REQUIRED)`, which accepts any
later `0.1.x` and refuses `0.2.0`.

### Uninstall

Remove the installed files, where `<target>` is `/usr/local` or the folder given when installing.

```sh
rm <target>/include/bpmn++.h
rm <target>/lib/libbpmn++.a
rm -rf <target>/lib/cmake/bpmnpp
```

The file `build/release/install_manifest.txt` lists the installed files.

## Example

An example using the library can be found in the [example folder](example). After installing, build it with

```sh
g++ -std=c++23 main.cpp -lbpmn++ -lxerces-c -o bpmn++
./bpmn++ diagram.bpmn
```

Explicitly provide include and lib folder by `-I<target>/include -L<target>/lib` if needed.
