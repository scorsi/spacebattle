# SpaceBattle Client

## Officially supported platforms

- MacOS (Latest: Mojave 10.14.1)
- Linux (Ubuntu 16.04 LTS and Ubuntu 18.04 LTS)

Windows may require adjustments in code
or build/execution process.

## Known issue with Jetbrains CLion

Sometimes, you can get linking issue inside CLion,
this is due to the default `CMake > Generation path` of Clion.

Open `Settings` (or `Preferences` for MacOS)
and go to `Build, Execution, Deployment`,
inside the `CMake` panel,
change `Generation path` from `cmake-build-debug` to `build`.

## How to compile code

```shell
# Create build directory
mkdir -p build
# Run commands inside build directory
cd build 
# Compile code
conan install ..
cmake ..
make
```

If you got issue, try to prepend `--build=missing` to the conan command.
If you still got issues, contact us via GitHub Issue
or by email to `sylvain.corsini@epitech.eu`.

## How to run program

```shell
# Go inside the build/bin directory
cd build/bin # Or bin if you already are in build directory
./spacebattle_client
```

### Run program outside build/bin directory

If you want to run the binary outside the `build/bin` folder.
Don't forget to add `LD_LIBRARY_PATH` or `DYLD_LIBRARY_PATH`,
to the execution command to correctly load the program,
depending of your platform: Linux, Windows or MacOS.
For more information about dynamic libraries, contact the support
of your actual OS.
