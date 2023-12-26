# bpmn++

## A BPMN parser library, written in C++.

This library provides a parser library for BPMN 2.0 allowing easy access to all elements and children (no getters or setters).

- **Download:** https://github.com/bpmn-os/bpmnpp
- **Documentation:** https://bpmn-os.github.io/bpmnpp 

## Dependencies

bpmn++ requires Xerces-C++ 3.2.x. On Ubuntu Linux Xerces can be installed by
```sh
sudo apt install libxerces-c-dev
```

Furthermore, `schematic++` must be available for the build process. You can obtain `schematic++` from https://github.com/rajgoel/schematicpp.

## Build the library

The library is built like a typical CMake project. A normal build from within the project folder will look something like this (output omitted):

```sh
mkdir build
cd build
cmake ..
make
```

This creates a single header file `lib/bpmn++.h` and a library `lib/libbpmn++.a`.

## Install the library
After library the program, it can be installed by

```
sudo make install
```

## Run tests
Tests can be run by

```
make tests
```

## Example

An example using the library can be found in `example` folder.

After successful installation of the library, you can build the example by

```sh
g++ -std=c++20 main.cpp -lbpmn++ -lxerces-c -o bpmn++
```

You can run the example by
```sh
./bpmn++ diagram.bpmn
```
