# Virtualization Prototyping Tool

# Build

Project is build with `cmake`, our prefered build system is `Ninja`, but it is
also possible to classic `make`. You are required to have installed these
dependencies:

* `SDL2`
* `SDL2_image`
* `GLFW3`
* `fmt`
* `spdlog`
* `glm`

In addition to that you have to have `git` and `glad` installed, as the `cmake`
scripts is going to download `ImGui` and generate `glad` libraries for you.

```bash
cmake -Bbuild -GNinja -DCMAKE_RELEASE_TYPE=Release .
cmake --build build
```

Additionaly, it is possible to switch to debug build using
`-DCMAKE_RELEASE_TYPE=Debug` instead of `Release`.

> [!TIP]
> `Release` is the default release type, thus if your target is only the release
> build, then you can omit the `CMAKE_RELEASE_TYPE` option entirely.

It is also possible to build the project with tests executable and source
documentation using additional option flags:
* `BUILD_TESTS` - builds test runtime executable as `<BUILDDIR>/bin/run_tests`
* `BUILD_DOCUMENTATION` - builds doxygen documentation which is going to be
  available in `<BUILDDIR>/Doxygen`
