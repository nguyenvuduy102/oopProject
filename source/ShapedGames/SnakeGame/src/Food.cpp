#include "../include/Food.h"
#include <cstdlib>
#include <ctime>

namespace Snake
{
    /**
     * @brief Constructs a Food object, initializing its appearance and random seed.
     */
    Food::Food()
    {
        m_food.setRadius(CELL / 2.f - 4.f);
        m_food.setOrigin({m_food.getRadius(), m_food.getRadius()});
        m_food.setFillColor(sf::Color::Red);
        std::srand(unsigned(std::time(nullptr)));
    }

    /**
     * @brief Spawns the food at a random position on the game grid.
     * @param w The width of the game window in pixels.
     * @param h The height of the game window in pixels.
     */
    void Food::spawn(unsigned w, unsigned h)
    {
        int cols = std::max(1, int(w) / int(CELL));
        int rows = std::max(1, int(h) / int(CELL));
        int x = std::rand() % cols;
        int y = std::rand() % rows;
        m_food.setPosition({float(x * CELL + CELL / 2), float(y * CELL + CELL / 2)});
    }

    /**
     * @brief Draws the food on the render target.
     * @param rt The SFML render target.
     */
    void Food::draw(sf::RenderTarget &rt) const
    {
        rt.draw(m_food);
    }

    /**
     * @brief Gets the bounding rectangle of the food for collision detection.
     * @return The global bounds of the food object.
     */
    sf::FloatRect Food::bounds() const
    {
        return m_food.getGlobalBounds();
    }
}