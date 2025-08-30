/**
 * @file Paddle.cpp
 * @brief Implementation of the Paddle class for Pong game paddles.
 */

#include "../include/Paddle.h"

namespace Pong
{
    /**
     * @brief Construct a new Paddle object.
     *
     * Initializes the paddle shape with the given size, position, and speed.
     *
     * @param size Size of the paddle as an sf::Vector2f.
     * @param pos Initial position of the paddle.
     * @param speed Movement speed of the paddle in pixels per update.
     */
    Paddle::Paddle(const sf::Vector2f &size, const sf::Vector2f &pos, float speed)
        : m_speed(speed)
    {
        m_shape.setSize(size);
        m_shape.setFillColor(sf::Color::White);
        m_shape.setPosition(pos);
    }

    /**
     * @brief Move the paddle upward.
     *
     * Decreases the paddle's y-position by its movement speed.
     */
    void Paddle::moveUp()
    {
        m_shape.move({0.f, -m_speed});
    }

    /**
     * @brief Move the paddle downward.
     *
     * Increases the paddle's y-position by its movement speed.
     */
    void Paddle::moveDown()
    {
        m_shape.move({0.f, m_speed});
    }

    /**
     * @brief Constrain the paddle within the window boundaries.
     *
     * Ensures that the paddle does not move outside the top or bottom
     * edges of the window.
     *
     * @param windowSize Size of the window as an sf::Vector2u.
     */
    void Paddle::updateBounds(const sf::Vector2u &windowSize)
    {
        if (m_shape.getPosition().y < 0.f)
            m_shape.setPosition({m_shape.getPosition().x, 0.f});

        if (m_shape.getPosition().y + m_shape.getSize().y > windowSize.y)
            m_shape.setPosition({m_shape.getPosition().x, windowSize.y - m_shape.getSize().y});
    }
}
