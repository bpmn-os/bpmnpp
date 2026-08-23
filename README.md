# bpmn++

## A BPMN parser library, written in C++.

This library provides a parser library for BPMN 2.0 allowing easy access to all elements and children (no getters or setters).

- **Download:** https://github.com/bpmn-os/bpmnpp
- **Documentation:** https://bpmn-os.github.io/bpmnpp

## Requirements

A C++23 compiler, GCC 15.2 or Clang 18.1.3 or later, CMake 3.26.4 or later, and git.

Other dependencies like Xerces-C++ 3.2.x or schematic++ are fetched automatically unless installed already.


## Build

To build bpmn++, run

```sh
mkdir build
cd build
cmake ..
make -j$(nproc)
```

This creates the single header `include/bpmn++.h` and the
library `lib/libbpmn++.a` in the `build/` folder.

The build type defaults to `Release`. Configure with 
```sh
cmake .. -DCMAKE_BUILD_TYPE=Debug
```
to keep assertions that are otherwise ignored.

### Documentation

To create the documentation, run

```sh
make docs
```

This creates the documentation in the `build/docs` folder.

**Note:** Building the documentation requires `doxygen` and `graphviz`. Run `sudo apt install doxygen graphviz` to install these.

### Tests

For testing, run
```sh
make -j$(nproc) tests
```

## Install

After building, run

```sh
sudo make install
```
to install bpmn++ into `/usr/local`, or

```sh
cmake --install <build> --prefix <target>
```
to copy
```
include/bpmn++.h
lib/libbpmn++.a
lib/cmake/bpmnpp/
```
from the `<build>` to the `<target>` folder.

A consumer can resolve the library with

```cmake
find_package(bpmnpp REQUIRED)
target_link_libraries(mytarget PRIVATE bpmnpp::bpmn++)
```

Nothing further is needed when bpmn++ was installed into `/usr/local`. For any other folder, the consumer
is built with `cmake .. -DCMAKE_PREFIX_PATH=<target>`.

A minimum version can be required, for instance `find_package(bpmnpp 0.1.0 REQUIRED)`, which accepts any
later `0.1.x` and refuses `0.2.0`.

### Uninstall

Remove the installed files, where `<target>` is `/usr/local` or the folder given when installing.

```sh
rm <target>/include/bpmn++.h
rm <target>/lib/libbpmn++.a
rm -rf <target>/lib/cmake/bpmnpp
```

The file `<build>/install_manifest.txt` lists the installed files.

## Example

An example using the library can be found in the `example` folder. After installing, build it with

```sh
g++ -std=c++23 main.cpp -lbpmn++ -lxerces-c -o bpmn++
./bpmn++ diagram.bpmn
```

Explicitly provide include and lib folder by `-I<target>/include -L<target>/lib` if needed.
