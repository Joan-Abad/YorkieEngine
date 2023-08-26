@echo off

rem Run CMake to configure the project
cmake .

rem Build the project using CMake
cmake --build .

rem Pause to keep the console window open
pause
