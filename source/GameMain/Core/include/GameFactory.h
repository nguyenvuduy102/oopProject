
/**
 * @file GameFactory.h
 * @brief Declares the GameFactory class for creating game instances.
 */
#pragma once
#include <memory>
#include <vector>
#include <string>
#include "IGame.h"


/**
 * @class GameFactory
 * @brief Factory class for creating game objects.
 */
class GameFactory
{
public:
    /**
     * @enum GameId
     * @brief Identifiers for supported games.
     */
    enum GameId
    {
        TETRIS = 0, /**< Tetris game. */
        SNAKE,      /**< Snake game. */
        PONG,       /**< Pong game. */
        FLAPPY      /**< Flappy game. */
    };

    /**
     * @brief Creates a game instance by ID.
     * @param id Game identifier.
     * @return Unique pointer to IGame instance.
     */
    static std::unique_ptr<IGame> create(GameId id);

    /**
     * @brief Gets the names of all available games.
     * @return Vector of game names.
     */
    static std::vector<std::string> gameNames();
};
