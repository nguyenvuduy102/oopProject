/**
 * @file Ball.cpp
 * @brief Implementation of the Ball class for the Pong game.
 */

#include "../include/Ball.h"
#include <random>

namespace Pong
{
    /**
     * @brief Construct a new Ball object.
     *
     * Initializes the ball with a given radius, sets its color to white,
     * centers its origin, and sets the initial velocity to zero.
     *
     * @param radius The radius of the ball (default is 10.f).
     */
    Ball::Ball(float radius)
    {
        m_shape.setRadius(radius);
        m_shape.setFillColor(sf::Color::White);
        m_shape.setOrigin({radius, radius});
        m_velocity = {0.f, 0.f};
    }

    /**
     * @brief Reset the ball's position and velocity.
     *
     * Places the ball at the center of the window and assigns a new random vertical velocity.
     * The horizontal velocity is set based on the given direction.
     *
     * @param windowSize The size of the game window.
     * @param direction The initial horizontal direction of the ball (positive = right, negative = left).
     */
    void Ball::reset(const sf::Vector2u &windowSize, int direction)
    {
        m_shape.setPosition({windowSize.x / 2.f, windowSize.y / 2.f});
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> dy(3.5f, 5.0f);
        float vy = dy(gen);
        m_velocity = {direction > 0 ? 15.f : -15.f, (gen() % 2 == 0) ? vy : -vy};
    }

    /**
     * @brief Update the ball's position based on its current velocity.
     */
    void Ball::update()
    {
        m_shape.move(m_velocity);
    }

    /**
     * @brief Invert the ball's horizontal velocity.
     *
     * Used when the ball collides with a paddle.
     */
    void Ball::invertX()
    {
        m_velocity.x = -m_velocity.x;
    }

    /**
     * @brief Invert the ball's vertical velocity.
     *
     * Used when the ball collides with the top or bottom of the window.
     */
    void Ball::invertY()
    {
        m_velocity.y = -m_velocity.y;
    }

    /**
     * @brief Set the ball's velocity.
     *
     * @param vel The new velocity vector.
     */
    void Ball::setVelocity(const sf::Vector2f &vel)
    {
        m_velocity = vel;
    }
}
