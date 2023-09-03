@echo off
:: cmake -G "Visual Studio 16 2019 Win64" 

::cmake -DGFX_BACKEND="d3d11" -DTARGET_PLATFORM="win64" -G "Visual Studio 16 2019" -S . -B ./CMakeSolutions
cmake -DGFX_BACKEND="d3d11" -DTARGET_PLATFORM="win64" -G "Visual Studio 17 2022" -S . -B ./CMakeSolutions
::cmake -G "Visual Studio 16 2019" -S . -B ./CMakeSolutions
pause

