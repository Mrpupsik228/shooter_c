# Shooter Game

A simple 2D shooter game built with C, SDL2, and SDL2_ttf.

## Features

- Control a rocket and shoot enemies.
- Score points by hitting enemies.
- Lose points and lives if enemies reach the bottom.
- Win by reaching a score of 10.
- Game over if you miss 3 enemies.

## Controls

- **A**: Move left
- **D**: Move right
- **Space**: Shoot

## Building

### Prerequisites

- C compiler (supporting C99)
- [CMake](https://cmake.org/) >= 3.10
- SDL2 and SDL2_ttf (automatically fetched if not found)
- Git if SDL2 or SDL2_ttf not found

### Steps

```sh
mkdir build
cd build
cmake ..
make
```