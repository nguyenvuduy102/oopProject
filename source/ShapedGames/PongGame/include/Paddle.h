#pragma once
#include <SFML/Graphics.hpp>

namespace Pong
{
    /**
     * @class Paddle
     * @brief Represents a paddle in the Pong game.
     *
     * The Paddle can move vertically within the game window and is used
     * to hit the ball back and forth. Each paddle has a size, position,
     * and movement speed.
     */
    class Paddle
    {
    public:
        /**
         * @brief Construct a new Paddle object.
         * 
         * @param size The size of the paddle (width, height).
         * @param pos The initial position of the paddle.
         * @param speed The speed at which the paddle moves vertically.
         */
        Paddle(const sf::Vector2f &size, const sf::Vector2f &pos, float speed);

        /**
         * @brief Move the paddle upward by its speed value.
         */
        void moveUp();

        /**
         * @brief Move the paddle downward by its speed value.
         */
        void moveDown();

        /**
         * @brief Keep the paddle within the bounds of the game window.
         * 
         * @param windowSize The size of the window, used to prevent 
         *        the paddle from moving outside the visible area.
         */
        void updateBounds(const sf::Vector2u &windowSize);

        /**
         * @brief Get the read-only reference to the paddle's shape.
         * 
         * @return const sf::RectangleShape& The rectangle shape representing the paddle.
         */
        const sf::RectangleShape &shape() const { return m_shape; }

        /**
         * @brief Get the modifiable reference to the paddle's shape.
         * 
         * @return sf::RectangleShape& The rectangle shape representing the paddle.
         */
        sf::RectangleShape &shape() { return m_shape; }

        /**
         * @brief Get the paddle's bounding rectangle.
         * 
         * @return sf::FloatRect The bounding box of the paddle, useful for collision detection.
         */
        sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

        /**
         * @brief Set the paddle's position.
         * 
         * @param pos The new position for the paddle.
         */
        void setPosition(const sf::Vector2f &pos) { m_shape.setPosition(pos); }

    private:
        sf::RectangleShape m_shape; ///< Rectangle shape representing the paddle.
        float m_speed;              ///< Movement speed of the paddle.
    };
}
