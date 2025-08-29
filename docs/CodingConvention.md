# Coding Style Guidelines

This document defines the coding conventions for the Game Hub project to ensure consistency, readability, and maintainability across the codebase.

## Language
- **Primary Language**: C++ (C++20 standard).
- **Framework**: SFML 3.0.0 for graphics, audio, and input handling.

## Formatting
- **Indentation**: Use 4 spaces (no tabs).
- **Line Length**: Maximum 120 characters per line.
- **Brace Style**: Allman style (braces on new lines).
  ```cpp
  void example()
  {
      // Code here
  }

File StructureHeader Files (.h): Contain declarations, includes, and class definitions.
Source Files (.cpp): Contain implementations.
Header Guards: Use #pragma once for simplicity and reliability.
Include Order:Standard library headers (e.g., <vector>, <iostream>).
Third-party headers (e.g., <SFML/Graphics.hpp>).
Project-specific headers (e.g., "GameCore.h").

Sort includes alphabetically within each group.
Use relative paths for project includes (e.g., ../include/GameCore.h).

cpp

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../include/GameCore.h"

Naming ConventionsClasses/Structs: PascalCase (e.g., GameCore, AudioManager).
Functions/Methods: camelCase (e.g., initGame, playSound).
Variables: snake_case (e.g., window_size, current_block).
Constants: SCREAMING_SNAKE_CASE (e.g., WINDOW_WIDTH, CELL_SIZE).
Private Members: Prefix with m_ (e.g., m_window, m_score).
Namespaces: PascalCase (e.g., Tetris, Snake).

CommentsUse Doxygen-style comments for classes, methods, and functions to enable documentation generation.cpp

/**
 * @brief Initializes the game with the given window.
 * @param window The SFML render window.
 * @return True if initialization succeeds, false otherwise.
 */
bool init(sf::RenderWindow& window) override;

Use // for inline comments to explain complex logic.cpp

// Check if block can move left without colliding
if (!isBlockOutside()) {
    m_currentBlock.move(0, -1);
}

Avoid redundant comments; focus on explaining why code exists rather than what it does.

Code OrganizationDirectory Structure

source/
├── GameMain/
│   ├── Core/           # Core game logic and interfaces (e.g., IGame, GameFactory)
│   └── Menu/           # Menu-related classes (e.g., Menu, MenuItem)
├── ShapedGames/
│   ├── TetrisGame/     # Tetris game implementation
│   ├── SnakeGame/      # Snake game implementation
│   ├── PongGame/       # Pong game implementation
│   └── FlappyBird/     # Flappy Bird implementation
├── assets/             # Fonts, images, music (e.g., monogram.ttf, background.png)
└── tests/              # Unit tests (e.g., test_tetris.cpp)

ImportsGroup includes by category (standard, SFML, project).
Sort alphabetically within each group.
Example:cpp

#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../include/Block.h"
#include "../include/Grid.h"

Error HandlingUse exceptions for critical errors (e.g., failure to load assets).cpp

if (!font.loadFromFile("assets/fonts/monogram.ttf")) {
    throw std::runtime_error("Failed to load font: assets/fonts/monogram.ttf");
}

Log non-critical errors to std::cerr for debugging.cpp

if (!texture.loadFromFile("assets/images/optional.png")) {
    std::cerr << "Warning: Optional texture not found, using default\n";
}

ToolsFormatter: Use clang-format to enforce consistent code style.yaml

BasedOnStyle: LLVM
IndentWidth: 4
ColumnLimit: 120

Run: clang-format -i source/**/*.cpp source/**/*.h to format all files in source/.

Linter: Use cppcheck for static code analysis.Run: cppcheck --enable=all --suppress=missingIncludeSystem source/ to detect issues.

Build System: Use CMake for project builds.Example CMakeLists.txt:cmake

cmake_minimum_required(VERSION 3.10)
project(GameHub)
find_package(SFML 3.0 COMPONENTS graphics audio REQUIRED)
add_executable(GameHub source/main.cpp)
target_link_libraries(GameHub sfml-graphics sfml-audio)

Run: cmake -B build && cmake --build build to build the project.

Best PracticesSOLID PrinciplesS (Single Responsibility): Each class has one responsibility.Example: Tetris::GameCore handles game logic, Tetris::GameRenderer handles rendering.

O (Open/Closed): Classes are open for extension but closed for modification.Example: New games implement IGame without modifying GameFactory.

L (Liskov Substitution): Derived classes can substitute their base class.Example: TetrisGame, SnakeGame can replace IGame.

I (Interface Segregation): Interfaces are minimal and focused.Example: IGame only includes init, run, cleanup, name.

D (Dependency Inversion): High-level modules depend on abstractions.Example: Tetris::GameController receives GameCore and AudioManager via constructor.

DRY (Don't Repeat Yourself)Reuse code through shared classes.Example: AudioManager handles sound across all games (Tetris, Snake, Pong, FlappyBird).

KISS (Keep It Simple, Stupid)Keep implementations simple to avoid unnecessary complexity.Example: Use straightforward game loops instead of complex state machines.

Example Codecpp

/**
 * @brief Manages the core logic of the Tetris game.
 */
class GameCore
{
public:
    /**
     * @brief Constructs a new GameCore instance.
     */
    GameCore() : m_score(0), m_paused(false) {}

    /**
     * @brief Moves the current block left if possible.
     */
    void moveLeft()
    {
        if (!m_paused)
        {
            m_currentBlock.move(0, -1);
            if (isBlockOutside())
            {
                m_currentBlock.move(0, 1); // Undo move if invalid
            }
        }
    }

private:
    int m_score;
    bool m_paused;
    Block m_currentBlock;

    /**
     * @brief Checks if the current block is outside the grid.
     * @return True if the block is outside, false otherwise.
     */
    bool isBlockOutside();
};

