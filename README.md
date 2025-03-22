# Pac-Man Game with Ghost AI

### Warning: The project is still not complete(runs partially).

![alt text](https://github.com/rejzzzz/pacman-game/tree/main/game-image.png)

## Description

This project is an ongoing development of a Pac-Man game, created using C and SDL. The goal is to implement a fully functional version of the classic Pac-Man game, featuring a playable character (Pac-Man) and AI-controlled ghosts. Currently, the ghost utilizes Dijkstra's Algorithm to navigate the maze and attempt to find the optimal path to Pac-Man.


## Features

- **Pac-Man Movement**: Control Pac-Man using keyboard inputs.
- **Ghost AI**: The ghost uses Dijkstra's Algorithm to navigate the maze and chase Pac-Man.
- **Maze Layout**: A grid-based maze where walls are represented, and paths are clear for movement.
- **Basic Rendering**: Graphics are rendered using the SDL library(in C).

## Technologies Used

- **C**: Programming language used for game logic and structure.
- **SDL**: A cross-platform library for multimedia and graphics.
- **Makefile**: Used for building the project and managing compilation.

## Installation

### Prerequisites

Make sure you have the following installed:

- GCC (GNU Compiler Collection)
- SDL2 development libraries
- Make

## For Linux
#### 1. Clone the Repo in  local machine

```bash
git clone https://github.com/rejzzzz/pacman-game.git
```
#### 2. Navigating to the Directory
```
cd pacman-game
```
#### 3. Installing Dependencies
```
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev
```
#### 4. Building the Project
```
make
```
#### 5. Running the Game
```
./pacman

```
