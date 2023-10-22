# a2s

The __a2s__ command utilizes `assimp` to convert 3d mesh files to SketchUp files.  Textures are not imported for any format.
See [here](https://github.com/assimp/assimp) for a list of formats supported by assimp.

## Usage

On the command line...

    > a2s input-file.ext

Creates a file named `input-file.ext.skp` in the same folder.

## Download

See the Release page for the latest download. Unzip the files, then move them to a directory in your `%PATH%.`

## Build Requirements

* [cmake](https://cmake.org/)
* ~~[premake5](https://github.com/premake/premake-core)~~ use cmake.
* [SketchUp SDK](https://developer.sketchup.com)
* A local clone of the `assimp` repository. [assimp](https://github.com/assimp/assimp)
* GNU `g++` compiler tools, bin utils, and `make` for Windows. See Note.

## Build Instructions

* set the `ASSIMP_SRC` variable in the `build-assimp.bat` file to your assimp source directory.
* run the `build-assimp.bat` file. This may take a few minutes.
* set the `SKETCHUP_SDK` and `ASSIMP` variable in the `Makefile` 
* run `make`

## Install

Once built, copy the `a2s.exe` file and the following 2 `dll` files to a folder on your `%PATH%`

* SketchUpAPI.dll
* SketchUpCommonPreferences.dll


## Notes

I use [scoop](https://scoop.sh/) to maintain the required dev tools on Windows.

__a2s__ defaults to using a SketchUp 8 file. Edit the `main.cpp` file if you want to change the default.


