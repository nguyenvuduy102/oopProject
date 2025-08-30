
/**
 * @file BaseGame.h
 * @brief Defines the BaseGame class, a base implementation for games.
 */
#pragma once
#include "IGame.h"


/**
 * @class BaseGame
 * @brief Base class for all games, implements IGame interface.
 */
class BaseGame : public IGame
{
public:
    /**
     * @brief Constructs a BaseGame object.
     * @param n Name of the game.
     * @param bg Background color.
     */
    BaseGame(const std::string &n, sf::Color bg);

    /**
     * @brief Initializes the game.
     * @param window Reference to the SFML render window.
     */
    void init(sf::RenderWindow &window) override;

    /**
     * @brief Runs the game loop.
     * @param window Reference to the SFML render window.
     */
    void run(sf::RenderWindow &window) override;

    /**
     * @brief Cleans up resources used by the game.
     */
    void cleanup() override;

    /**
     * @brief Gets the name of the game.
     * @return Name as a string.
     */
    std::string name() const override;

private:
    std::string m_name; /**< Name of the game. */
    sf::Color m_bg;     /**< Background color. */

protected:
    /**
     * @brief Gets the background color.
     * @return Background color.
     */
    sf::Color getBackgroundColor() const { return m_bg; }
};
