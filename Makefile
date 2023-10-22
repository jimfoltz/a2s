SHELL = cmd.exe

SKETCHUP_SDK = $(USERPROFILE)\SketchUp\SDK\latest

ASSIMP = $(USERPROFILE)/Repos/assimp
ASSIMPLIB = assimp-build\lib\libassimp.a
ZLIB = assimp-build/contrib/zlib/libzlibstatic.a
HEADERS = -I$(SKETCHUP_SDK)/headers -I$(ASSIMP)/include -I./assimp-build/include
DLLS = $(SKETCHUP_SDK)\binaries\sketchup\x64\*.dll

CXXFLAGS = -Wall -m64 -static -static-libgcc -static-libstdc++ -std=c++17



a2s.exe: main.cpp $(ASSIMPLIB) $(ZLIB)
	g++ $(CXXFLAGS) -o $@ $< $(HEADERS) $(SKETCHUP_SDK)\binaries\sketchup\x64\sketchupapi.dll $(ASSIMPLIB) $(ZLIB)
	copy $(DLLS) .
	
clean:
	del a2s.exe
	del *.dll
	del libassimp.a

