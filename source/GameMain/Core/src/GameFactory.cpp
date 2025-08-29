#include "../include/GameFactory.h"
#include "../include/BaseGame.h"

// Create a game based on given ID
std::unique_ptr<IGame> GameFactory::create(GameId id)
{
    // Pick which game to make based on ID
    switch (id)
    {
    case TETRIS:                                                            // If Tetris picked
        return std::make_unique<BaseGame>("Tetris", sf::Color(20, 20, 80)); // Make Tetris with dark blue background
    case SNAKE:                                                             // If Snake picked
        return std::make_unique<BaseGame>("Snake", sf::Color(20, 80, 20));  // Make Snake with green background
    case PONG:                                                              // If Pong picked
        return std::make_unique<BaseGame>("Pong", sf::Color(80, 20, 20));   // Make Pong with red background
    case FLAPPY:                                                            // If Flappy Bird picked
        return std::make_unique<BaseGame>("Flappy", sf::Color(80, 80, 20)); // Make Flappy with yellowish background
    default:                                                                // If ID don’t match nothing
        return nullptr;                                                     // Return nothing, no game made
    }
}

// Get list of game names
std::vector<std::string> GameFactory::gameNames()
{
    // Return array of all game names we got
    return {"Tetris", "Snake", "Pong", "Flappy Bird"};
}