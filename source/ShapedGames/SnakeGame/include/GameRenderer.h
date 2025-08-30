#pragma once
#include <SFML/Graphics.hpp>
#include "GameController.h"

namespace Snake
{
    /**
     * @brief Manages rendering of the Snake game, including the game grid, snakes, food, and UI elements.
     */
    class GameRenderer
    {
    public:
        /**
         * @brief Constructs a GameRenderer with a reference to the render window.
         * @param window The SFML render window for drawing.
         */
        GameRenderer(sf::RenderWindow &window);

        /**
         * @brief Renders the current game state based on the controller's mode.
         * @param controller The GameController providing the game state.
         */
        void render(const GameController &controller);

    private:
        sf::RenderWindow &m_window; ///< Reference to the SFML render window.
        sf::Font m_font;            ///< Font used for rendering text (e.g., scores, menu).
    };
}