@echo off
set SOURCE=main.c
set OUTPUT=main.exe

clang %SOURCE% -o %OUTPUT% -D_CRT_SECURE_NO_WARNINGS

if %errorlevel% equ 0 (
    echo Compilation successful. Executable created: %OUTPUT%
    echo.
    %OUTPUT%
) else (
    echo Compilation failed.
)
