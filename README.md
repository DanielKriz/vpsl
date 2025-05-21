# Virtualization Prototyping Shading Language

This is the repository of `vpsl` -- a high-level directive-based extension of
already existing shading languages.


https://github.com/user-attachments/assets/f4cb03e4-e465-4749-9bef-54c2f1c17064


# Build

Project is build with `cmake`, our preferred build system is `Ninja`, but it is
also possible to classic `make`. The project is primarily build using the
`vpckg` package manager. There are several build workflows present and to build
you can use this command:

```bash
cmake --workflow --preset Release
```

There is also support for `Debug` workflow, that is used for development and the
`Test` workflow, which is basically the same as debug workflow, but it also runs
the tests after a successful build.

The provided CMake script is going to download a fresh installation of `vpckg`.

# Prerequisites

* [CMake](https://cmake.org/)
* [Ninja](https://ninja-build.org/)
* C++ compiler with C++23 support

Rest of the dependencies is going to be downloaded with the `vpckg`.
