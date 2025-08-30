#include "../include/GameFactory.h"
#include "../include/BaseGame.h"
#include "../../../ShapedGames/FlappyBird/include/FlappyGame.h"
#include "../../../ShapedGames/PongGame/include/PongGame.h"
#include "../../../ShapedGames/SnakeGame/include/SnakeGame.h"
#include "../../../ShapedGames/TetrisGame/include/TetrisGame.h"

// Create a game based on given ID
std::unique_ptr<IGame> GameFactory::create(GameId id)
{
    // Pick which game to make based on ID
    switch (id)
    {
    case TETRIS:                                       // If Tetris picked
        return std::make_unique<Tetris::TetrisGame>(); // Make Tetris with dark blue background
    case SNAKE:                                        // If Snake picked
        return std::make_unique<Snake::SnakeGame>();   // Make Snake with green background
    case PONG:                                         // If Pong picked
        return std::make_unique<Pong::PongGame>();     // Make Pong with red background
    case FLAPPY:                                       // If Flappy Bird picked
        return std::make_unique<Flappy::FlappyGame>(); // Make Flappy with yellowish background
    default:                                           // If ID don’t match nothing
        return nullptr;                                // Return nothing, no game made
    }
}

// Get list of game names
std::vector<std::string> GameFactory::gameNames()
{
    // Return array of all game names we got
    return {"Tetris", "Snake", "Pong", "Flappy Bird"};
}