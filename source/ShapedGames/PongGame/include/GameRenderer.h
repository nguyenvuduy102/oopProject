#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

namespace Pong
{
    /**
     * @class GameRenderer
     * @brief Responsible for rendering all visual elements of the Pong game.
     *
     * This class handles loading graphical resources (fonts, texts) and 
     * drawing the paddles, ball, and scores onto the game window.
     */
    class GameRenderer
    {
    public:
        /**
         * @brief Constructor for the GameRenderer class.
         */
        GameRenderer();

        /**
         * @brief Load graphical resources such as fonts.
         *
         * This method must be called before rendering to ensure all 
         * required assets are available.
         */
        void load();

        /**
         * @brief Render the current game state onto the given window.
         *
         * Draws paddles, ball, and score text to the render target.
         *
         * @param window The render window where the game is drawn.
         * @param left The left paddle to render.
         * @param right The right paddle to render.
         * @param ball The ball to render.
         * @param leftScore The current score of the left player.
         * @param rightScore The current score of the right player.
         */
        void render(sf::RenderWindow &window,
                    const Paddle &left,
                    const Paddle &right,
                    const Ball &ball,
                    int leftScore,
                    int rightScore);

    private:
        sf::Font m_font;     ///< Font used for rendering the score text.
        sf::Text m_scoreText; ///< Text object used for displaying scores.
    };
}
