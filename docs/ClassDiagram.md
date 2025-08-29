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

class GameMain_Menu {
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

class GameMain_MenuItem {
    -m_text: sf::Text
    -m_background: sf::RectangleShape
    -m_isSelected: bool
    -m_animationTime: float
    +setSelected(selected: bool) void
    +update(dt: float) void
    +draw(window: sf::RenderWindow) void
}

class GameMain_SnowBackground {
    -m_window: sf::RenderWindow&
    -m_snowflakes: vector~Snowflake~
    -m_topColor: sf::Color
    -m_rng: mt19937
    +update(dt: float) void
}

class GameMain_FadeEffect {
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

class Tetris_TetrisGame {
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

class Tetris_GameCore {
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

class Tetris_GameRenderer {
    -font: sf::Font&
    -bgTexture: sf::Texture
    -bgSprite: unique_ptr~sf::Sprite~
    +draw(window: sf::RenderWindow, core: GameCore, choice: int, paused: bool) void
    +drawNext(window: sf::RenderWindow, block: Block) void
}

class Tetris_GameController {
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

class Tetris_Block {
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

class Tetris_Grid {
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

class Tetris_AudioManager {
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

class Snake_SnakeGame {
    -renderer: GameRenderer*
    -audio: AudioManager
    -controller: GameController
    -initialized: bool
    +init(window: sf::RenderWindow) void
    +run(window: sf::RenderWindow) void
    +cleanup() void
    +name() string
}

class Snake_GameController {
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

class Snake_Snake {
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

class Snake_Food {
    -m_food: sf::CircleShape
    +spawn(w: unsigned, h: unsigned) void
    +draw(rt: sf::RenderTarget) void
    +bounds() sf::FloatRect
}

class Snake_GameRenderer {
    -window: sf::RenderWindow&
    -font: sf::Font
    +render(controller: GameController) void
}

class Snake_AudioManager {
    -music: sf::Music
    -eatSound: unique_ptr~sf::Sound~
    -gameOverSound: unique_ptr~sf::Sound~
    +playEat() void
    +playGameOver() void
    +playMusic() void
    +stopMusic() void
}

class Pong_PongGame {
    -core: GameCore
    -renderer: GameRenderer
    +init(window: sf::RenderWindow) void
    +run(window: sf::RenderWindow) void
    +cleanup() void
    +name() string
}

class Pong_GameCore {
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

class Pong_Paddle {
    -m_shape: sf::RectangleShape
    -m_speed: float
    +moveUp() void
    +moveDown() void
    +updateBounds(windowSize: sf::Vector2u) void
    +shape() sf::RectangleShape&
}

class Pong_Ball {
    -m_shape: sf::CircleShape
    -m_velocity: sf::Vector2f
    +reset(windowSize: sf::Vector2u, direction: int) void
    +update() void
    +invertX() void
    +invertY() void
    +shape() sf::CircleShape&
}

class Pong_GameRenderer {
    -font: sf::Font
    -scoreText: sf::Text
    +load() void
    +render(window: sf::RenderWindow, left: Paddle, right: Paddle, ball: Ball, leftScore: int, rightScore: int) void
}

class Pong_AudioManager {
    -bounceSound: sf::Sound
    -scoreSound: sf::Sound
    +load() void
    +playBounce() void
    +playScore() void
}

class Flappy_FlappyGame {
    -textures: TextureManager
    -core: GameCore*
    -renderer: GameRenderer*
    +init(window: sf::RenderWindow) void
    +run(window: sf::RenderWindow) void
    +cleanup() void
    +name() string
}

class Flappy_GameCore {
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

class Flappy_Bird {
    -textures: TextureManager&
    -m_sprite: sf::Sprite
    -m_velocity: float
    -m_frame: int
    +reset(windowSize: sf::Vector2u) void
    +flap(impulse: float) void
    +update(gravity: float, frames: int, animate: bool, physics: bool) void
    +sprite() sf::Sprite&
}

class Flappy_Pipe {
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

class Flappy_GameRenderer {
    -textures: TextureManager&
    -font: sf::Font
    -scoreText: sf::Text
    -background: array~sf::Sprite, 6~
    -gameover: sf::Sprite
    +load() void
    +render(window: sf::RenderWindow, bird: Bird, pipes: deque~Pipe~, score: int, state: GameState, frames: int) void
}

class Flappy_TextureManager {
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

class Flappy_AudioManager {
    -flapSound: sf::Sound
    -scoreSound: sf::Sound
    -hitSound: sf::Sound
    +load() void
    +playFlap() void
    +playScore() void
    +playHit() void
}

IGame <|.. BaseGame
IGame <|.. Tetris_TetrisGame
IGame <|.. Snake_SnakeGame
IGame <|.. Pong_PongGame
IGame <|.. Flappy_FlappyGame
GameFactory --> IGame
GameManager --> GameFactory
GameMain_Menu --> GameManager
GameMain_Menu *-- GameMain_MenuItem
GameMain_Menu *-- GameMain_SnowBackground
GameMain_Menu *-- GameMain_FadeEffect
Tetris_TetrisGame *-- Tetris_GameCore
Tetris_TetrisGame *-- Tetris_GameRenderer
Tetris_TetrisGame *-- Tetris_GameController
Tetris_GameController --> Tetris_GameCore
Tetris_GameController --> Tetris_GameRenderer
Tetris_GameController --> Tetris_AudioManager
Tetris_GameCore *-- Tetris_Grid
Tetris_GameCore *-- Tetris_Block
Snake_SnakeGame *-- Snake_GameController
Snake_SnakeGame *-- Snake_GameRenderer
Snake_SnakeGame *-- Snake_AudioManager
Snake_GameController *-- Snake_Snake
Snake_GameController *-- Snake_Food
Snake_GameController --> Snake_AudioManager
Pong_PongGame *-- Pong_GameCore
Pong_PongGame *-- Pong_GameRenderer
Pong_GameCore *-- Pong_Paddle
Pong_GameCore *-- Pong_Ball
Pong_GameCore *-- Pong_AudioManager
Flappy_FlappyGame *-- Flappy_GameCore
Flappy_FlappyGame *-- Flappy_GameRenderer
Flappy_FlappyGame *-- Flappy_TextureManager
Flappy_GameCore *-- Flappy_Bird
Flappy_GameCore *-- Flappy_Pipe
Flappy_GameCore *-- Flappy_AudioManager
Flappy_GameCore --> Flappy_TextureManager
Flappy_GameRenderer --> Flappy_TextureManager
Flappy_Bird --> Flappy_TextureManager
Flappy_Pipe --> Flappy_TextureManager
