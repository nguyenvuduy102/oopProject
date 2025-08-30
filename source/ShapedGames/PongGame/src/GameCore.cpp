/**
 * @file GameCore.cpp
 * @brief Implementation of the GameCore class for the Pong game.
 */

#include "../include/GameCore.h"

namespace Pong
{
    /**
     * @brief Construct a new GameCore object.
     *
     * Initializes paddles, ball, and scores with default values.
     * - Left paddle is positioned on the left side of the window.
     * - Right paddle is positioned on the right side of the window.
     * - Ball is created with a radius of 30.f.
     */
    GameCore::GameCore()
        : m_left({40.f, 180.f}, {20.f, 460.f}, 6.5f),
          m_right({40.f, 180.f}, {1920.f - 20 * 2.f, 460.f}, 6.5f),
          m_ball(30.f),
          m_leftScore(0),
          m_rightScore(0)
    {
    }

    /**
     * @brief Initialize the game.
     *
     * Loads audio resources and places the ball in the center
     * with an initial direction.
     *
     * @param windowSize The size of the game window.
     */
    void GameCore::init(const sf::Vector2u &windowSize)
    {
        m_audio.load();
        resetBall(windowSize, 1);
    }

    /**
     * @brief Update the game state.
     *
     * Handles ball movement, paddle bounds checking, collisions,
     * scoring logic, and triggers sound effects accordingly.
     *
     * @param windowSize The size of the game window.
     */
    void GameCore::update(const sf::Vector2u &windowSize)
    {
        m_ball.update();
        m_left.updateBounds(windowSize);
        m_right.updateBounds(windowSize);

        // Ball and paddle collision
        if (m_ball.getBounds().findIntersection(m_left.getBounds()) ||
            m_ball.getBounds().findIntersection(m_right.getBounds()))
        {
            m_ball.invertX();
            m_audio.playBounce();
        }

        // Ball and top/bottom collision
        if (m_ball.getPosition().y - 10.f <= 0.f ||
            m_ball.getPosition().y + 10.f >= windowSize.y)
        {
            m_ball.invertY();
            m_audio.playBounce();
        }

        // Left wall: right player scores
        if (m_ball.getPosition().x < 0.f)
        {
            m_rightScore++;
            m_audio.playScore();
            resetBall(windowSize, 1);
        }

        // Right wall: left player scores
        if (m_ball.getPosition().x > windowSize.x)
        {
            m_leftScore++;
            m_audio.playScore();
            resetBall(windowSize, -1);
        }
    }

    /**
     * @brief Handle player input.
     *
     * Controls:
     * - W/S: Move left paddle up/down.
     * - Up/Down arrow keys: Move right paddle up/down.
     */
    void GameCore::handleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            m_left.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            m_left.moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            m_right.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            m_right.moveDown();
    }

    /**
     * @brief Reset the ball to the center with a new velocity.
     *
     * @param windowSize The size of the game window.
     * @param direction The horizontal direction for the ball (1 = right, -1 = left).
     */
    void GameCore::resetBall(const sf::Vector2u &windowSize, int direction)
    {
        m_ball.reset(windowSize, direction);
    }
}
