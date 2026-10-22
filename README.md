# cub3D — Raycasting Engine

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" alt="C" />
  <img src="https://img.shields.io/badge/Graphics-MiniLibX-black?style=for-the-badge" alt="MiniLibX" />
  <img src="https://img.shields.io/badge/42-Yerevan-black?style=for-the-badge" alt="42 Yerevan" />
</p>

## About

**cub3D** is a graphics project developed as part of the 42 School curriculum. The goal is to create a first-person 3D-like game environment from a two-dimensional map using the **raycasting technique**.

Inspired by classic games such as *Wolfenstein 3D*, the project explores how a 2D grid can be transformed into an immersive first-person perspective.

Written in C, the program reads a `.cub` configuration file, validates the map and its settings, loads wall textures, and renders the environment using MiniLibX.

The project combines graphics programming, mathematical calculations, file parsing, memory management, and real-time input handling.

## Features

- **Raycasting:** Render a first-person perspective from a 2D map.
- **Textured walls:** Display directional wall textures.
- **Map parsing:** Read map layouts and configuration data from `.cub` files.
- **Map validation:** Check map structure, configuration values, and valid player placement.
- **Player movement:** Navigate the environment using the keyboard.
- **Camera rotation:** Look around the environment.
- **Collision detection:** Prevent movement through walls.
- **Floor and ceiling rendering:** Apply configured colors to the scene.
- **Resource management:** Release allocated resources when the program exits.

*Keep only the features implemented in your version of the project.*

## How It Works

The rendering process transforms the map into a first-person view using raycasting.

```text
        .cub Configuration
                |
                v
         Parse and Validate
                |
                v
          Initialize Game
                |
                v
          Cast Rays
                |
                v
      Detect Wall Intersections
                |
                v
       Calculate Wall Distance
                |
                v
       Apply Wall Textures
                |
                v
         Render the Frame
                |
                v
          Display Window
```

For each frame, rays are cast from the player's position into the map. The distance to each wall intersection determines the projected height of the wall on the screen.

The renderer selects the appropriate wall texture according to the intersection direction and draws the resulting vertical strips to create the illusion of depth.

## Graphics and Raycasting

Raycasting is the core technique behind the project.

The game uses a two-dimensional map to represent the world. Instead of rendering full 3D geometry, it calculates intersections between rays and the map's grid to determine which walls are visible.

The main concepts include:

- Ray direction and player orientation.
- Grid traversal and wall intersection detection.
- Distance calculations and perspective projection.
- Wall orientation and texture mapping.
- Frame rendering and keyboard event handling.

This approach provides a practical introduction to graphics programming and the mathematics behind early first-person games.

## Map Configuration

The game accepts a `.cub` file as a command-line argument.

A configuration file typically contains wall texture paths, floor and ceiling colors, and the map layout.

### Example `.cub` File

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111111
100000001
1000N0001
100000001
111111111
```

### Configuration Elements

| Identifier | Description |
|:---:|---|
| `NO` | North wall texture |
| `SO` | South wall texture |
| `WE` | West wall texture |
| `EA` | East wall texture |
| `F` | Floor color in RGB format |
| `C` | Ceiling color in RGB format |

### Map Characters

| Character | Meaning |
|:---:|---|
| `1` | Wall |
| `0` | Walkable space |
| `N` | Player starting position, facing north |
| `S` | Player starting position, facing south |
| `E` | Player starting position, facing east |
| `W` | Player starting position, facing west |
| Space | Map padding or void, subject to map validation rules |

A valid map must follow the official subject's rules, including valid characters, appropriate wall enclosure, and exactly one player starting position.

## Controls

| Key | Action |
|:---:|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit the game |
| Window close button | Close the game |

The exact movement behavior depends on the implementation. Additional controls, such as mouse rotation or a minimap, can be documented if supported.

## Installation and Usage

### Requirements

- C compiler (`cc` or `gcc`).
- GNU Make.
- MiniLibX or MLX42, depending on the implementation.
- The graphics libraries and system dependencies required by the selected MiniLibX version.

On Linux, a traditional MiniLibX setup may require X11 development libraries. MLX42 generally uses GLFW and CMake, so install the dependencies appropriate to your repository.

### Clone the Repository

```bash
git clone https://github.com/ETamazyan/cub3D.git
cd cub3D
```

### Compile

```bash
make
```

The Makefile builds the executable and any required project libraries.

### Run

```bash
./cub3D maps/map.cub
```

Replace `maps/map.cub` with the path to a valid map in your repository.

The program expects a `.cub` map file as an argument.

## Makefile Commands

| Command | Description |
|---|---|
| `make` | Compile the project |
| `make all` | Build the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the executable |
| `make re` | Clean and rebuild |

These are conventional targets; use the commands actually provided by your Makefile.

## Technologies

- **C** — Core implementation and game logic.
- **MiniLibX / MLX42** — Window management, graphics rendering, and input events.
- **Raycasting** — First-person rendering technique.
- **Makefile** — Compilation and build automation.
- **Git and GitHub** — Version control and project documentation.

## Skills Developed

Through this project, I have practiced:

- Understanding raycasting and perspective projection.
- Working with vectors, angles, and distance calculations.
- Parsing and validating structured input files.
- Loading and rendering image textures.
- Handling real-time keyboard input and window events.
- Implementing player movement and collision detection.
- Managing dynamically allocated memory and graphics resources.
- Organizing a multi-file C project.
- Debugging graphics applications.
- Working within the constraints of the 42 curriculum.

## Project Structure

The exact directory layout depends on the implementation. A typical structure may look like this:

```text
cub3D/
├── Makefile
├── README.md
├── includes/
│   └── cub3d.h
├── src/
│   ├── main.c
│   ├── parsing/
│   ├── raycasting/
│   ├── rendering/
│   ├── player/
│   └── utils/
├── maps/
│   └── map.cub
├── textures/
└── libft/
```

Adapt the tree to reflect your actual files and directories.

## What I Learned

cub3D strengthened my understanding of low-level programming and connected mathematical concepts with interactive graphics.

The project provided hands-on experience in transforming structured map data into a visual environment, managing input events, and coordinating parsing, rendering, and resource cleanup in a C application.

## Authors

**42 Yerevan Student: etamazya, maavalya**

Part of my learning journey at 42 Yerevan.

GitHub: [@Etamazyan](https://github.com/Etamazyan)

---

*Exploring graphics programming, one ray at a time.*
