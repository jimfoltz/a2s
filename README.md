# a2s
__a2s__ is a basic, command line mesh to sketchup converter.  Textures are not imported for any format.
See [here](https://github.com/assimp/assimp) for a list of formats supported by assimp.

## Requirements

* [cmake](https://cmake.org/) (for building assimp)
* [premake5](https://github.com/premake/premake-core) (because it's easier than cmake)
* [SketchUp SDK](https://extensions.sketchup.com/sketchup-sdk)

## Build

    $ premake5 vs2019
    $ msbuild -p:Configuration=Release build

Running `premake` creates a `build` folder where the project files are stored. 

## Install

Once built, copy the `a2s.exe` file and following required `dll` files to a folder on your `%PATH%`


* SketchUpAPI.dll
* SketchUpCommonPreferences.dll
* assimp-vc142-mt.dll

All the files should be located in the `build/bin/Win64/Release` folder.

## Usage


    > a2s input-file.ext

Creates a file named `input-file.ext.skp` in the same folder.

## Notes

I use [scoop](https://scoop.sh/) to maintain installations of `cmake` and `premake` on Windows. 

__a2s__ defaults to using a SketchUp version 2016 file. Edit the `main.cpp` file if you want to change the default.


