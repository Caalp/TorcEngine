@echo off
cmake -DGFX_BACKEND="d3d11" -DTARGET_PLATFORM="win64" -G "Visual Studio 17 2022" -S . -B ./CMakeSolutions
pause

