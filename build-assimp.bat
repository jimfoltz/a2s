setlocal


set ASSIMP_SRC=%USERPROFILE%\Repos\assimp

if [%1]==[-r] (
  rd /q/s assimp-build
)

md assimp-build 2>nul

pushd assimp-build

cmake -S %ASSIMP_SRC% ^
  -G "MinGW Makefiles" ^
  -DBUILD_SHARED_LIBS=OFF ^
  -DASSIMP_NO_EXPORT=ON ^
  -DASSIMP_BUILD_ASSIMP_TOOLS=OFF ^
  -DASSIMP_BUILD_TESTS=OFF ^ 

cmake --build .

popd
