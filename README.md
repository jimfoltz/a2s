# a2s

The __a2s__ command utilizes `assimp` to convert 3d mesh files to SketchUp files.

See [here](https://assimp-docs.readthedocs.io/en/latest/about/introduction.html) for a list of formats supported by assimp.

This is a basic converter which relies completely on the capabilities of
`assimp` for the conversion.  If `assimp` can not handle the conversion, no
further attempt is made. Many formats result in poor or unexpected models.
Textures are not imported for any format. Scale is fixed and set to a larger value to
over-come SketchUp's "small geometry" limitation.

`.stl` and `.ply` files seem to work well, which was the original goal of the code.

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


