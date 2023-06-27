# bpmn++
## A BPMN parser library, written in C++.

## Purpose/goals
The purpose of this library is to provide a parser library for BPMN 2.0 allowing easy access to all elements and children (no getters or setters).

## Dependencies

bpmn++ requires Xerces-C++ 3.2.x. On Ubuntu Linux Xerces can be installed by
```sh
sudo apt install libxerces-c-dev
```

Furthermore, `schematic++` must be available for the build process. You can obtain `schematic++` from https://github.com/rajgoel/schematicpp.

## Build the library

The library is built like a typical CMake project. A normal build will look something like this (output omitted):

```sh
 ~/bpmnpp$ mkdir build
 ~/bpmnpp$ cd build
 ~/bpmnpp/build$ cmake ..
 ~/bpmnpp/build$ make
 ```

This creates a single header file `lib/bpmn++.h` and a library `lib/libbpmn++.a`.

## Install the library
After library the program, it can be installed by

```
~/bpmnpp/build$ sudo make install
```

## Example

An example using the library can be found in `example` folder.

After successful installation of the library, you can build the example by

```sh
cd ~/bpmnpp/example
g++ -std=c++20 main.cpp -lbpmn++ -lxerces-c -o bpmn++
```

You can run the example by
```sh
cd ~/bpmnpp/example
./bpmn++ diagram.bpmn
```
