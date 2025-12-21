# Snake Game 🐍

Pequeño proyecto de juego tipo Snake escrito en C++ usando Raylib.

## Descripción

Este es un proyecto simple para experimentar con Raylib y lógica de juegos básicos. El ejecutable generado se llama `app` y el código fuente principal está en `src/main.cpp`.

⚙️ Compilador: `clang++` (estoy usando `clang++` para compilar en macOS).

## Dependencias

- clang++ (C++17)
- raylib (biblioteca gráfica)
- macOS frameworks: OpenGL, Cocoa, IOKit, CoreVideo

## Compilar (ejemplo)

Puedes compilar con el siguiente comando (ya incluido como tarea en el proyecto):

```bash
clang++ src/main.cpp -o app -std=c++17 -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

## Ejecutar

Después de compilar:

```bash
./app
```

## Git

Este repositorio incluye un `.gitignore` que omite binarios y archivos temporales (por ejemplo, `app`).

Comandos básicos para iniciar con Git (si aún no lo hiciste):

```bash
git init
git add .
git commit -m "Initial commit: add README and .gitignore"
```

## Notas

- El `.gitignore` ya tiene entradas comunes (binarios, archivos de IDE, archivos locales y secretos).
- Si necesitas que añada un archivo de build (Makefile / CMake) o instrucciones más detalladas, dime y lo agrego.

¡Disfruta programando! ✅
