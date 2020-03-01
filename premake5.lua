
-- Vars
assimp_src = "C:/Users/Jim/Code/Repos/assimp"
su_sdk = "C:/Users/Jim/SketchUp/SDK/latest"
config = "Release"

workspace "A2S"
  configurations { "Debug", "Release" }
  platforms { "Win64" }
  location "build"
  architecture "x86_64"


project "assimp"
  kind "Makefile"
  location "build/assimp"
  buildcommands {
     "cmake"
     .. " -D ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT:BOOL=OFF"
     .. " -D ASSIMP_NO_EXPORT:BOOL=ON"
     .. " -D ASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF"
     .. " -D ASSIMP_BUILD_TESTS:BOOL=OFF"
     .. " -D BUILD_SHARED_LIBS:BOOL=ON "
     .. assimp_src
     , "cmake --build . --config " .. config
  }


project "a2s"
  dependson "assimp"
  location "build"
  kind  "ConsoleApp"
  language "C++"

  files { "*.h", "*.cpp" }

  includedirs { su_sdk .. "/headers" }
  includedirs { assimp_src .. "/include" }
  includedirs { "build/assimp/include" }

  libdirs { su_sdk .. "/binaries/sketchup/x64"}
  libdirs { "build/assimp/lib/" .. config }

  links { "SketchUpAPI", "assimp-vc142-mt" }

  filter {"action:*"}

  postbuildcommands {
      "{COPY} c:/users/jim/sketchup/sdk/latest/binaries/sketchup/x64/SketchUpAPI.dll %{cfg.buildtarget.directory}",
      "{COPY} c:/users/jim/sketchup/sdk/latest/binaries/sketchup/x64/SketchUpCommonPreferences.dll %{cfg.buildtarget.directory}",
      "{COPY} %{wks.location}/assimp/bin/release/assimp-vc142-mt.dll %{cfg.buildtarget.directory}"
  }

