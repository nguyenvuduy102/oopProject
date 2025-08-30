/**
 * @file GameRenderer.cpp
 * @brief Implementation of the GameRenderer class for rendering Pong game objects.
 */

#include "../include/GameRenderer.h"

namespace Pong
{
    /**
     * @brief Construct a new GameRenderer object.
     *
     * Initializes the score text with the font (to be loaded later),
     * an empty string, and a default character size of 58.
     */
    GameRenderer::GameRenderer() : m_scoreText(m_font, "", 58) {}

    /**
     * @brief Load rendering resources.
     *
     * Loads the font used for rendering the score text.
     * If the font cannot be loaded, a runtime error is thrown.
     */
    void GameRenderer::load()
    {
        if (!m_font.openFromFile("../source/assets/fonts/monogram.ttf"))
            throw std::runtime_error("Failed to load font: assets/fonts/monogram.ttf");

        m_scoreText.setFillColor(sf::Color::White);
    }

    /**
     * @brief Render all game objects onto the window.
     *
     * Clears the window, draws the paddles, the ball, and the current score,
     * then displays the updated frame.
     *
     * @param window Reference to the game window.
     * @param left Left paddle object.
     * @param right Right paddle object.
     * @param ball Ball object.
     * @param leftScore Current score of the left player.
     * @param rightScore Current score of the right player.
     */
    void GameRenderer::render(sf::RenderWindow &window,
                              const Paddle &left,
                              const Paddle &right,
                              const Ball &ball,
                              int leftScore,
                              int rightScore)
    {
        // Clear background with dark gray color
        window.clear(sf::Color(20, 20, 20));

        // Draw paddles and ball
        window.draw(left.shape());
        window.draw(right.shape());
        window.draw(ball.shape());

        // Draw score text
        m_scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
        m_scoreText.setPosition({window.getSize().x / 2.f - 50.f, 20.f});
        window.draw(m_scoreText);

        // Display the rendered frame
        window.display();
    }
}
