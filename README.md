# big_uint
big_uint is a C library that implements arbitrary-length unsigned integers.

## Getting the library
The library may be cloned from Github as follows:
```sh
git clone --recurse-submodules git@github.com:Kirisummer/big_uint.git
```

## Building
### Requirements
Building requires C11-compliant compiler, cmake, make, and [tinytest](https://github.com/ccosmin/tinytest) present in repo root (downloaded as git submodule) for testing.

### Doing The Thing
The library uses CMake as a build system. Building the library itself:
```sh
cmake -B build
make -C build
```

Assuming the library is placed into a separate directory in current directory,
statically linking the library may be done as follows:
```cmake
target_include_directories(${YOUR_TARGET} PRIVATE big_uint/include)
target_link_libraries(${YOUR_TARGET} PRIVATE big_uint)
```

### Testing
Tests may be ran as follows:
```sh
build/test/big_uint_test
```

## License
big_uint is licensed under MIT license with personal ML exception.
