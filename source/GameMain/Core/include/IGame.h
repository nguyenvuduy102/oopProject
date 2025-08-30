
/**
 * @file IGame.h
 * @brief Declares the IGame interface for all games.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class IGame
 * @brief Interface for game classes.
 */
class IGame
{
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~IGame() = default;

    /**
     * @brief Initializes the game.
     * @param window Reference to the SFML render window.
     */
    virtual void init(sf::RenderWindow &window) = 0;

    /**
     * @brief Runs the game loop.
     * @param window Reference to the SFML render window.
     */
    virtual void run(sf::RenderWindow &window) = 0;

    /**
     * @brief Cleans up resources used by the game.
     */
    virtual void cleanup() = 0;

    /**
     * @brief Gets the name of the game.
     * @return Name as a string.
     */
    virtual std::string name() const = 0;
};
