#pragma once
#include <SFML/Graphics.hpp>

namespace Snake
{
    constexpr unsigned WINDOW_W = 1920; ///< Window width in pixels.
    constexpr unsigned WINDOW_H = 1080; ///< Window height in pixels.
    constexpr unsigned CELL = 60;       ///< Size of each grid cell in pixels.

    /**
     * @brief Represents a food item in the Snake game that the snake can consume to grow.
     */
    class Food
    {
    public:
        /**
         * @brief Constructs a Food object, initializing its appearance.
         */
        Food();

        /**
         * @brief Spawns the food at a random position on the game grid.
         * @param w The width of the game window in pixels.
         * @param h The height of the game window in pixels.
         */
        void spawn(unsigned w, unsigned h);

        /**
         * @brief Draws the food on the render target.
         * @param rt The SFML render target.
         */
        void draw(sf::RenderTarget &rt) const;

        /**
         * @brief Gets the bounding rectangle of the food for collision detection.
         * @return The global bounds of the food object.
         */
        sf::FloatRect bounds() const;

    private:
        sf::CircleShape m_food; ///< The visual representation of the food (a circle).
    };
}