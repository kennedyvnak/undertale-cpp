@echo off
REM Conan setup
conan install . --build missing
REM Generate sln
"vendor/premake/premake5" vs2022
