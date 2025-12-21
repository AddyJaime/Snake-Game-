git add .
git commit -m "Initial commit: add README and .gitignore"

# Snake Game 🐍

Small Snake-style game project written in C++ using Raylib.

## Description

This is a simple project to experiment with Raylib and basic game logic. The generated executable is named `app` and the main source file is `src/main.cpp`.

⚙️ Compiler: `clang++` (this project uses `clang++` on macOS).

## Dependencies

- clang++ (C++17)
- raylib (graphics library)
- macOS frameworks: OpenGL, Cocoa, IOKit, CoreVideo

## Build (example)

You can build the project with the following command (also included as a task in the project):

```bash
clang++ src/main.cpp -o app -std=c++17 -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

## Run

After building:

```bash
./app
```

## Git

This repository includes a `.gitignore` that excludes binaries and temporary files (for example, `app`).

Basic Git commands to get started (if you haven't already):

```bash
git init
git add .
git commit -m "Initial commit: add README and .gitignore"
```

## Notes

- The `.gitignore` already contains common entries (binaries, editor/IDE files, local config, and secrets).
- If you'd like, I can add a build file (Makefile / CMake) or more detailed instructions—just tell me which you prefer.

Enjoy coding! ✅
