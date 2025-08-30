#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Food.h"

namespace Snake
{
    /**
     * @brief Represents a single segment of the snake's body.
     */
    struct Segment
    {
        sf::RectangleShape shape; ///< The visual representation of the segment.
        /**
         * @brief Constructs a Segment with a position, size, and color.
         * @param pos The position of the segment.
         * @param size The size of the segment (default: CELL x CELL).
         * @param c The color of the segment (default: Green).
         */
        Segment(sf::Vector2f pos = {0, 0}, sf::Vector2f size = {CELL, CELL}, sf::Color c = sf::Color::Green)
        {
            shape.setSize(size);
            shape.setPosition(pos);
            shape.setFillColor(c);
        }
    };

    /**
     * @brief Represents a snake in the game, consisting of multiple segments.
     */
    class Snake
    {
    public:
        /**
         * @brief Constructs an empty Snake object.
         */
        Snake();

        /**
         * @brief Initializes the snake with a starting position, color, and direction.
         * @param headPos The starting position of the snake's head.
         * @param col The color of the snake.
         * @param dir The initial direction of the snake.
         */
        void init(sf::Vector2f headPos, sf::Color col, sf::Vector2f dir);

        /**
         * @brief Updates the snake's position based on its direction.
         */
        void update();

        /**
         * @brief Sets the snake's direction, preventing direct reversal.
         * @param d The new direction vector.
         */
        void setDirection(sf::Vector2f d);

        /**
         * @brief Gets the current direction of the snake.
         * @return The current direction vector.
         */
        sf::Vector2f getDirection() const;

        /**
         * @brief Gets the position of the snake's head.
         * @return The position of the head segment, or (0,0) if the snake is empty.
         */
        sf::Vector2f headPos() const;

        /**
         * @brief Increases the snake's length by adding a new segment.
         */
        void grow();

        /**
         * @brief Draws the snake on the render target.
         * @param rt The SFML render target.
         */
        void draw(sf::RenderTarget &rt) const;

        /**
         * @brief Checks if the snake has collided with itself.
         * @return True if the head collides with any other segment, false otherwise.
         */
        bool checkSelfCollision() const;

        /**
         * @brief Gets the list of snake segments.
         * @return A const reference to the vector of segments.
         */
        const std::vector<Segment> &body() const { return m_body; }

    private:
        std::vector<Segment> m_body;         ///< List of snake segments.
        sf::Vector2f m_dir{0, 0};           ///< Current direction of the snake.
        std::vector<sf::Vector2f> m_history; ///< History of head positions for movement.
        int m_delay = 1;                    ///< Delay factor for segment movement.
    };
}