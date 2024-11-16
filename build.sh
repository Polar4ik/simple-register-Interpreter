#!/bin/bash

SOURCE="main.c"
OUTPUT="main.exe"

# Компиляция
clang "$SOURCE" -o "$OUTPUT" -D_CRT_SECURE_NO_WARNINGS

# Проверка кода возврата компиляции
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable created: $OUTPUT"
    echo
    ./"$OUTPUT"
else
    echo "Compilation failed."
fi
