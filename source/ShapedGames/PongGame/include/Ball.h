#pragma once
#include <SFML/Graphics.hpp>

namespace Pong
{
    /**
     * @class Ball
     * @brief Represents the ball in the Pong game, handling its movement, position, and collisions.
     */
    class Ball
    {
    public:
        /**
         * @brief Constructor for the Ball class.
         * @param radius The radius of the ball (default is 10.f).
         */
        Ball(float radius = 10.f);

        /**
         * @brief Reset the ball position to the center of the window and set its initial direction.
         * @param windowSize The size of the render window.
         * @param direction The horizontal direction of the ball (-1 for left, 1 for right).
         */
        void reset(const sf::Vector2u &windowSize, int direction);

        /**
         * @brief Update the ball's position based on its velocity.
         */
        void update();

        /**
         * @brief Invert the horizontal velocity (used when bouncing off vertical surfaces).
         */
        void invertX();

        /**
         * @brief Invert the vertical velocity (used when bouncing off horizontal surfaces).
         */
        void invertY();

        /**
         * @brief Set the velocity of the ball.
         * @param vel The new velocity vector.
         */
        void setVelocity(const sf::Vector2f &vel);

        /**
         * @brief Get the ball shape (const version).
         * @return A const reference to the ball's CircleShape.
         */
        const sf::CircleShape &shape() const { return m_shape; }

        /**
         * @brief Get the ball shape (non-const version).
         * @return A reference to the ball's CircleShape.
         */
        sf::CircleShape &shape() { return m_shape; }

        /**
         * @brief Get the global bounds of the ball (used for collision detection).
         * @return A FloatRect representing the ball's bounds.
         */
        sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

        /**
         * @brief Get the current position of the ball.
         * @return The ball's position as a 2D vector.
         */
        sf::Vector2f getPosition() const { return m_shape.getPosition(); }

        /**
         * @brief Set the position of the ball.
         * @param pos The new position of the ball.
         */
        void setPosition(const sf::Vector2f &pos) { m_shape.setPosition(pos); }

    private:
        sf::CircleShape m_shape;   ///< The drawable circle representing the ball.
        sf::Vector2f m_velocity;   ///< The current velocity of the ball.
    };
}
