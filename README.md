# Phantom Dash Game

A simple 2D platformer game built using **C++** and **Raylib**.  
Inspired by Mario, but with a twist — you can't attack enemies, only dodge them!

---

## 🕹️ Game Features
- Dodge enemies and collect points
- Reach the finish line to complete the level
- Two fully playable levels implemented
- Simple animations, collision detection, and scoring
- Retro arcade-like gameplay

---

## 📁 Project Structure
- `main.cpp`: Main game loop and setup
- `Levels.cpp`: Handles level design and transitions
- `Menu.cpp`: Displays the main menu
- `Player.cpp`: Controls the player movement and logic
- `Enemies.cpp`: Manages enemy behavior
- `Animations.cpp`: Simple sprite animations

---

## 🛠️ How to Build

Make sure you have **Raylib** installed and properly configured with g++.

Compile the project using:

```bash
g++ -o main.exe main.cpp Levels.cpp Menu.cpp Player.cpp Enemies.cpp Animations.cpp -lraylib -lopengl32 -lgdi32 -lwinmm

.\main.exe
