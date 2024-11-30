@echo off
set SOURCE=strs_tests.c
set OUTPUT=strs_tests.exe

clang %SOURCE% -o %OUTPUT% -D_CRT_SECURE_NO_WARNINGS

if %errorlevel% equ 0 (
    echo Compilation successful. Executable created: %OUTPUT%
    echo.
    %OUTPUT%
) else (
    echo Compilation failed.
)
