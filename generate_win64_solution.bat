@echo off
set BUILD_FOLDER=.\build\windows_vs2022
set TARGET_PLATFORM=Windows
set DIR_3RDPARTY=.\3rdParty

echo checking and installing for dependencies
rem --path takes calling directory as current directory, so everything relative to where it is called
::python Config/Build/download_dependencies.py --path=dependencies.json

rem actually build and create solution for the project

:: GFX_BACKEND flag tells engine which dll to load in runtime for the graphics backend, currently only d3d11 is supported
:: TARGET_PLATFORM is to tell which platform files to compile, currently only for windows 64bit
cmake -DGFX_BACKEND="d3d11" -DTARGET_PLATFORM=%TARGET_PLATFORM% -G "Visual Studio 17 2022" -S . -B %BUILD_FOLDER%

pause

