##
<h1><img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/covers/cover-cub3d.png"</h1>

## Description
42_cube3D is a project from the 42 school, inspired by the classic game Wolfenstein 3D, considered the first "First Person Shooter" (FPS) in gaming history. This project immerses you in the technique of raycasting to create a dynamic view within a maze, where the goal is to find your way while learning the basics of graphical development in C with MiniLibX.

## 🚀 Objectives
- Create a realistic 3D graphical representation of a maze using raycasting.
- Use MiniLibX for window management, textures, and event handling.
- Explore graphical programming concepts such as colors, textures, and perspective effects.

## 🛠️ Features
- 3D Rendering with Raycasting: Generating a 3D view from a 2D environment.
- Texture Management: Different textures for each wall (north, south, east, west).
- Player Controls: Movement with W, A, S, D keys and camera rotation with left/right arrow keys.
- Color Management: Different colors for the floor and ceiling.
- User Interaction: Clean exit from the application with the ESC key or the window's close button.

## ⚙️ Installation
To install and run the project, follow these steps:
1. Clone the repository:
```
git clone https://github.com/cypri1-dev/42_cube3D.git
cd 42_cube3D
```
2. Compile the project using the Makefile:
```
make
```
3. Run the program with a game map as an argument:
```
./cub3D [map].cub
```
## 📄 Map Examples
Here is an example of a minimal .cub file:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
111111
100001
101101
1000N1
111111
```
## 🎮 Controls
- Movement Keys: W, A, S, D.
- Camera Rotation: Left/Right arrow keys.
- Exit: Esc or click on the close button.

## 📚 Useful Resources
- [Wolfenstein 3D - Original Game](http://users.atw.hu/wolf3d/)

##
Feel free to add more details or make any modifications as needed!
