# Blade: C++ SDL2 CMake Emscripten Boilerplate Code

This is boilerplate code for using Emscripten with CMake and SDL2.

## Building

To build for emscripten target set `EMSDK` environment to path of emsdk installation, and use CMake Presets to build. 

The CMake Prefix works well with VSCode.

### In CLI

- To List Presets
  
```
cmake --list-presets
```

- To build

```
cmake --preset <preset_name> -S . -B ./build
```