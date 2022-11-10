@echo off
REM Conan setup
conan install . --build missing -s build_type=Debug
REM Generate sln
"vendor/premake/premake5" vs2022
