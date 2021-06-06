# klib
A personal library of useful pieces of code, very intuitively named klib, short for "Kian's Library" :)

# Dependencies
Currently, the only dependencies of this project are the C++ standard library and Catch2, assuming you would like to build unit tests.

# Building
This project uses CMake as its build system. The library is currently a header-only library that provides an `INTERFACE` CMake target.
In order to build tests, you can use the following commands:
```
mkdir build
cd build
cmake ../
make
```

Once tests are built, you may run them by using the following:
```
make test
```
