# `big_uint`
`big_uint` is a C library that implements arbitrary-length unsigned integers.

## Getting the library
The library may be cloned from Github as follows:
```sh
git clone --recurse-submodules git@github.com:Kirisummer/big_uint.git
```

## Building
### Requirements
Building requires C11-compliant compiler, CMake, make, and [tinytest](https://github.com/ccosmin/tinytest) present in repo root (downloaded as git submodule) for testing.

The library is checked to be working with:
- GCC 13.2.1
- CMake 3.27.7
- make 4.4.1
- tinytest revision used as a submodule

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

## Usage
If allocation or some other fail factor is present for library function, the function returns
a struct with enums, or a enum.
Enum values should be checked for corresponding SUCCESS value for further usage of `big_uint`.
If an allocation fails, `big_uint` should not be used at worst and must freed at best.

"Binary" operators work as augmented assignment operators, i.e. they mutate
the left argument. `big_uint`'s value, however, may be copied to other `big_uint`.
Keep in mind you need to check the allocation for success after the copying.

`big_uint`-s may be passed as values for reading, and must be passed by pointer for mutation.

## License
`big_uint` is licensed under MIT license with personal ML exception.
Check [LICENSE](LICENSE) for more details.
