
/**
 * @file GameFactory.cpp
 * @brief Implements the GameFactory class methods.
 */

#include "../include/GameFactory.h"
#include "../include/BaseGame.h"

/**
 * @brief Creates a game instance by ID.
 * @param id Game identifier.
 * @return Unique pointer to IGame instance.
 */
std::unique_ptr<IGame> GameFactory::create(GameId id)
{
    switch (id)
    {
    case TETRIS:
        return std::make_unique<BaseGame>("Tetris", sf::Color(20, 20, 80));
    case SNAKE:
        return std::make_unique<BaseGame>("Snake", sf::Color(20, 80, 20));
    case PONG:
        return std::make_unique<BaseGame>("Pong", sf::Color(80, 20, 20));
    case FLAPPY:
        return std::make_unique<BaseGame>("Flappy", sf::Color(80, 80, 20));
    default:
        return nullptr;
    }
}

/**
 * @brief Gets the names of all available games.
 * @return Vector of game names.
 */
std::vector<std::string> GameFactory::gameNames()
{
    return {"Tetris", "Snake", "Pong", "Flappy Bird"};
}
