# Software Architecture

This document describes the architecture of the Game Hub project, a multi-game application built using SFML.

## Overview
The Game Hub is a desktop application that allows users to play multiple classic games (Tetris, Snake, Pong, Flappy Bird) through a unified menu interface. The system is built using C++ with SFML for graphics, audio, and input handling.

## Architecture
The project follows a **Layered Architecture** to separate concerns and improve maintainability. The layers are:

1. **Presentation Layer**:
   - **Components**: `Menu`, `MenuItem`, `SnowBackground`, `FadeEffect`, `GameRenderer` (per game).
   - **Purpose**: Handles user interface, rendering, and user input.
   - **Example**: The `Menu` class displays the main menu and handles navigation, while `GameRenderer` classes draw game-specific graphics.

2. **Business Logic Layer**:
   - **Components**: `GameCore` (per game), `GameController` (per game), `GameManager`, `GameFactory`.
   - **Purpose**: Manages game logic, state, and rules.
   - **Example**: `Tetris::GameCore` handles block movement and scoring, `GameManager` manages game selection.

3. **Data Layer**:
   - **Components**: `settings.txt` for persistent settings, `Grid` (Tetris), `Block` (Tetris), `Snake` (Snake), etc.
   - **Purpose**: Manages game state and persistent data.
   - **Example**: `GameManager` loads/saves the selected game index to `settings.txt`.

## Design Patterns
- **Factory Pattern**: `GameFactory` creates game instances based on `GameId`.
- **Singleton Pattern**: `GameManager` uses a singleton to manage global game selection state.
- **Strategy Pattern**: The `IGame` interface allows different games to implement their own logic while adhering to a common contract.
- **Dependency Injection**: Game controllers receive dependencies (e.g., `GameCore`, `AudioManager`) via constructor injection.

## Technology Stack
- **Language**: C++20.
- **Framework**: SFML 3.0.0 for graphics, audio, and input.
- **Build System**: CMake.
- **Tools**: `clang-format` for formatting, `cppcheck` for linting, Google Test for unit testing.

## Module Descriptions
1. **Core Module** (`GameMain/Core`):
   - Contains `IGame`, `BaseGame`, `GameFactory`, `GameManager`.
   - Manages game creation and selection logic.
2. **Menu Module** (`GameMain/Menu`):
   - Handles the main menu and settings UI with animated effects (snow, fade).
3. **Game Modules** (`ShapedGames/*`):
   - Each game (Tetris, Snake, Pong, Flappy Bird) is a separate module with its own `GameCore`, `GameRenderer`, and `GameController`.
   - Follows MVC-like structure within each game:
     - **Model**: `GameCore` (game state and logic).
     - **View**: `GameRenderer` (rendering).
     - **Controller**: `GameController` (input handling, updating model).

## Data Flow
1. User interacts with `Menu` to select a game.
2. `GameManager` retrieves the selected game index and uses `GameFactory` to create an `IGame` instance.
3. The game instance (`TetrisGame`, `SnakeGame`, etc.) initializes its components (`GameCore`, `GameRenderer`, `GameController`).
4. The game loop (`run`) processes input, updates state, and renders graphics via SFML.

## Non-Functional Requirements
- **Performance**: 60 FPS rendering using `window.setFramerateLimit(60)`.
- **Scalability**: Modular design allows adding new games by implementing `IGame`.
- **Maintainability**: Clear separation of concerns and consistent coding style.
- **Reliability**: Exception handling for asset loading and file I/O.

## Diagram
Below is a high-level architecture diagram using Mermaid:

```mermaid
classDiagram
    class IGame {
        <<interface>>
        +init(window: sf::RenderWindow) void
        +run(window: sf::RenderWindow) void
        +cleanup() void
        +name() string
    }

    class BaseGame {
        -m_name: string
        -m_bg: sf::Color
        +init(window: sf::RenderWindow) void
        +run(window: sf::RenderWindow) void
        +cleanup() void
        +name() string
        #getBackgroundColor() sf::Color
    }

    class GameFactory {
        +create(id: GameId) unique_ptr~IGame~
        +gameNames() vector~string~
    }

    class GameManager {
        <<singleton>>
        -selected: int
        +instance() GameManager&
        +setSelected(idx: int) void
        +getSelected() int
        +createSelectedGame() unique_ptr~IGame~
        +loadSettings() void
        +saveSettings() void
    }

    namespace GameMain {
        class Menu {
            -m_window: sf::RenderWindow&
            -m_font: sf::Font
            -m_options: vector~MenuItem~
            -m_selectedIndex: int
            -m_background: SnowBackground
            -m_music: sf::Music
            -m_clickSound: sf::Sound
            +run() int
            +runSettings() int
            -moveUp() void
            -moveDown() void
        }

        class MenuItem {
            -m_text: sf::Text
            -m_background: sf::RectangleShape
            -m_isSelected: bool
            -m_animationTime: float
            +setSelected(selected: bool) void
            +update(dt: float) void
            +draw(window: sf::RenderWindow) void
        }

        class SnowBackground {
            -m_window: sf::RenderWindow&
            -m_snowflakes: vector~Snowflake~
            -m_topColor: sf::Color
            -m_rng: mt19937
            +update(dt: float) void
        }

        class FadeEffect {
            -overlay: sf::RectangleShape
            -mode: Mode
            -timer: float
            -totalTime: float
            +startFadeIn(duration: float) void
            +startFadeOut(duration: float) void
            +update(dt: float) void
            +draw(window: sf::RenderWindow) void
            +isFading() bool
        }
    }

    namespace Tetris {
        class TetrisGame {
            -core: GameCore
            -audio: AudioManager
            -font: sf::Font
            -renderer: GameRenderer*
            -controller: GameController*
            +init(window: sf::RenderWindow) void
            +run(window: sf::RenderWindow) void
            +cleanup() void
            +name() string
        }

        class GameCore {
            -grid: Grid
            -blocks: vector~Block~
            -currentBlock: Block
            -nextBlock: Block
            -score: int
            -linesClearedTotal: int
            -level: int
            -paused: bool
            -gameOver: bool
            +moveLeft() void
            +moveRight() void
            +moveDown() StepResult
            +rotate() bool
            +reset() void
            +getScore() int
            +getLines() int
            +getLevel() int
            +isPaused() bool
            +togglePause() void
        }

        class GameRenderer {
            -font: sf::Font&
            -bgTexture: sf::Texture
            -bgSprite: unique_ptr~sf::Sprite~
            +draw(window: sf::RenderWindow, core: GameCore, choice: int, paused: bool) void
            +drawNext(window: sf::RenderWindow, block: Block) void
        }

        class GameController {
            -core: GameCore&
            -audio: AudioManager&
            -renderer: GameRenderer&
            -inputClock: sf::Clock
            -moveDelay: float
            +handleInput(window: sf::RenderWindow) void
            +update() void
            +render(window: sf::RenderWindow) void
            +getGameOverChoice() int
            +isPaused() bool
        }

        class Block {
            -id: int
            -cells: map~int, vector~Position~~
            -cellSize: int
            -rotationState: int
            -rowOffset: int
            -columnOffset: int
            +draw(window: sf::RenderWindow, offsetX: int, offsetY: int) void
            +move(rows: int, columns: int) void
            +rotate() void
            +undoRotation() void
            +getCellPositions() vector~Position~
        }

        class Grid {
            -grid: int[20][12]
            -numRows: int
            -numCols: int
            -cellSize: int
            -colors: vector~sf::Color~
            +initialize() void
            +draw(window: sf::RenderWindow) void
            +isCellOutside(row: int, col: int) bool
            +isCellEmpty(row: int, col: int) bool
            +clearFullRows() int
        }

        class AudioManager {
            -rotateSound: sf::Sound
            -clearSound: sf::Sound
            -gameOverSound: sf::Sound
            -music: sf::Music
            +playRotate() void
            +playClear() void
            +playGameOver() void
            +playMusic() void
            +stopMusic() void
        }
    }

    namespace Snake {
        class SnakeGame {
            -renderer: GameRenderer*
            -audio: AudioManager
            -controller: GameController
            -initialized: bool
            +init(window: sf::RenderWindow) void
            +run(window: sf::RenderWindow) void
            +cleanup() void
            +name() string
        }

        class GameController {
            -audio: AudioManager&
            -p1: Snake
            -p2: Snake
            -food: Food
            -score1: int
            -score2: int
            -mode: Mode
            +init() void
            +update() void
            +handleEvent(event: optional~sf::Event~) void
            +mode() Mode
            +player1() Snake&
            +player2() Snake&
            +food() Food&
            +score1() int
            +score2() int
        }

        class Snake {
            -body: vector~Segment~
            -dir: sf::Vector2f
            -history: vector~sf::Vector2f~
            +init(headPos: sf::Vector2f, col: sf::Color, dir: sf::Vector2f) void
            +update() void
            +setDirection(d: sf::Vector2f) void
            +grow() void
            +draw(rt: sf::RenderTarget) void
            +checkSelfCollision() bool
            +headPos() sf::Vector2f
        }

        class Food {
            -m_food: sf::CircleShape
            +spawn(w: unsigned, h: unsigned) void
            +draw(rt: sf::RenderTarget) void
            +bounds() sf::FloatRect
        }

        class GameRenderer {
            -window: sf::RenderWindow&
            -font: sf::Font
            +render(controller: GameController) void
        }

        class AudioManager {
            -music: sf::Music
            -eatSound: unique_ptr~sf::Sound~
            -gameOverSound: unique_ptr~sf::Sound~
            +playEat() void
            +playGameOver() void
            +playMusic() void
            +stopMusic() void
        }
    }

    namespace Pong {
        class PongGame {
            -core: GameCore
            -renderer: GameRenderer
            +init(window: sf::RenderWindow) void
            +run(window: sf::RenderWindow) void
            +cleanup() void
            +name() string
        }

        class GameCore {
            -left: Paddle
            -right: Paddle
            -ball: Ball
            -leftScore: int
            -rightScore: int
            -audio: AudioManager
            +init(windowSize: sf::Vector2u) void
            +update(windowSize: sf::Vector2u) void
            +handleInput() void
            +leftPaddle() Paddle&
            +rightPaddle() Paddle&
            +ball() Ball&
            +leftScore() int
            +rightScore() int
        }

        class Paddle {
            -m_shape: sf::RectangleShape
            -m_speed: float
            +moveUp() void
            +moveDown() void
            +updateBounds(windowSize: sf::Vector2u) void
            +shape() sf::RectangleShape&
        }

        class Ball {
            -m_shape: sf::CircleShape
            -m_velocity: sf::Vector2f
            +reset(windowSize: sf::Vector2u, direction: int) void
            +update() void
            +invertX() void
            +invertY() void
            +shape() sf::CircleShape&
        }

        class GameRenderer {
            -font: sf::Font
            -scoreText: sf::Text
            +load() void
            +render(window: sf::RenderWindow, left: Paddle, right: Paddle, ball: Ball, leftScore: int, rightScore: int) void
        }

        class AudioManager {
            -bounceSound: sf::Sound
            -scoreSound: sf::Sound
            +load() void
            +playBounce() void
            +playScore() void
        }
    }

    namespace Flappy {
        class FlappyGame {
            -textures: TextureManager
            -core: GameCore*
            -renderer: GameRenderer*
            +init(window: sf::RenderWindow) void
            +run(window: sf::RenderWindow) void
            +cleanup() void
            +name() string
        }

        class GameCore {
            -textures: TextureManager&
            -bird: Bird
            -pipes: deque~Pipe~
            -audio: AudioManager
            -score: int
            -gravity: float
            -flapImpulse: float
            +init(windowSize: sf::Vector2u) void
            +update(windowSize: sf::Vector2u, delta: float, frames: int) void
            +handleInput(state: GameState, newState: GameState&) void
            +bird() Bird&
            +pipes() deque~Pipe~
            +score() int
            +reset(windowSize: sf::Vector2u) void
        }

        class Bird {
            -textures: TextureManager&
            -m_sprite: sf::Sprite
            -m_velocity: float
            -m_frame: int
            +reset(windowSize: sf::Vector2u) void
            +flap(impulse: float) void
            +update(gravity: float, frames: int, animate: bool, physics: bool) void
            +sprite() sf::Sprite&
        }

        class Pipe {
            -m_upper: sf::Sprite
            -m_lower: sf::Sprite
            -m_scored: bool
            +update(speed: float) void
            +upper() sf::Sprite&
            +lower() sf::Sprite&
            +isOffScreen() bool
            +hasScored() bool
            +setScored() void
        }

        class GameRenderer {
            -textures: TextureManager&
            -font: sf::Font
            -scoreText: sf::Text
            -background: array~sf::Sprite, 6~
            -gameover: sf::Sprite
            +load() void
            +render(window: sf::RenderWindow, bird: Bird, pipes: deque~Pipe~, score: int, state: GameState, frames: int) void
        }

        class TextureManager {
            -bird: array~sf::Texture, 3~
            -pipe: sf::Texture
            -background: sf::Texture
            -gameover: sf::Texture
            +load() void
            +getBird(frame: int) sf::Texture&
            +getPipe() sf::Texture&
            +getBackground() sf::Texture&
            +getGameover() sf::Texture&
        }

        class AudioManager {
            -flapSound: sf::Sound
            -scoreSound: sf::Sound
            -hitSound: sf::Sound
            +load() void
            +playFlap() void
            +playScore() void
            +playHit() void
        }
    }

    IGame <|.. BaseGame : Inheritance
    IGame <|.. Tetris::TetrisGame : Inheritance
    IGame <|.. Snake::SnakeGame : Inheritance
    IGame <|.. Pong::PongGame : Inheritance
    IGame <|.. Flappy::FlappyGame : Inheritance
    GameFactory --> IGame : Creates
    GameManager --> GameFactory : Uses
    GameMain::Menu --> GameManager : Uses
    GameMain::Menu *-- GameMain::MenuItem : Composition
    GameMain::Menu *-- GameMain::SnowBackground : Composition
    GameMain::Menu *-- GameMain::FadeEffect : Composition
    Tetris::TetrisGame *-- Tetris::GameCore : Composition
    Tetris::TetrisGame *-- Tetris::GameRenderer : Composition
    Tetris::TetrisGame *-- Tetris::GameController : Composition
    Tetris::GameController --> Tetris::GameCore : Dependency
    Tetris::GameController --> Tetris::GameRenderer : Dependency
    Tetris::GameController --> Tetris::AudioManager : Dependency
    Tetris::GameCore *-- Tetris::Grid : Composition
    Tetris::GameCore *-- Tetris::Block : Composition
    Snake::SnakeGame *-- Snake::GameController : Composition
    Snake::SnakeGame *-- Snake::GameRenderer : Composition
    Snake::SnakeGame *-- Snake::AudioManager : Composition
    Snake::GameController *-- Snake::Snake : Composition
    Snake::GameController *-- Snake::Food : Composition
    Snake::GameController --> Snake::AudioManager : Dependency
    Pong::PongGame *-- Pong::GameCore : Composition
    Pong::PongGame *-- Pong::GameRenderer : Composition
    Pong::GameCore *-- Pong::Paddle : Composition
    Pong::GameCore *-- Pong::Ball : Composition
    Pong::GameCore *-- Pong::AudioManager : Composition
    Flappy::FlappyGame *-- Flappy::GameCore : Composition
    Flappy::FlappyGame *-- Flappy::GameRenderer : Composition
    Flappy::FlappyGame *-- Flappy::TextureManager : Composition
    Flappy::GameCore *-- Flappy::Bird : Composition
    Flappy::GameCore *-- Flappy::Pipe : Composition
    Flappy::GameCore *-- Flappy::AudioManager : Composition
    Flappy::GameCore --> Flappy::TextureManager : Dependency
    Flappy::GameRenderer --> Flappy::TextureManager : Dependency
    Flappy::Bird --> Flappy::TextureManager : Dependency
    Flappy::Pipe --> Flappy::TextureManager : Dependency