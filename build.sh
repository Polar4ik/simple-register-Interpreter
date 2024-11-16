#!/bin/bash

SOURCE="main.c"
OUTPUT="main.exe"

clang "$SOURCE" -o "$OUTPUT" -D_CRT_SECURE_NO_WARNINGS

if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable created: $OUTPUT"
    echo
    ./"$OUTPUT"
else
    echo "Compilation failed."
fi
