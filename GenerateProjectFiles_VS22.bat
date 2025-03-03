@echo off
REM Change to the directory where this script is located
cd /d %~dp0

if not exist "build" (
    mkdir build
)
cd build
cmake -G "Visual Studio 17 2022" ..
pause
