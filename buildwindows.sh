#!/bin/bash

# Compile the program
x86_64-w64-mingw32-gcc -o bin/Game.exe src/*.c -Iinclude -Llib -lSDL3 -lSDL3_image -lm

# Check if the compilation was successful
if [ $? -eq 0 ]; then
  echo "Compilation successful. Running the program..."
  wine bin/Game.exe
else
  echo "Compilation failed. Program not executed."
fi
