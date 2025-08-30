#include "../include/Food.h"
#include <cstdlib>
#include <ctime>

namespace Snake
{
    Food::Food()
    {
        m_food.setRadius(CELL / 2.f - 4.f);
        m_food.setOrigin({m_food.getRadius(), m_food.getRadius()});
        m_food.setFillColor(sf::Color::Red);
        std::srand(unsigned(std::time(nullptr)));
    }

    void Food::spawn(unsigned w, unsigned h)
    {
        int cols = std::max(1, int(w) / int(CELL));
        int rows = std::max(1, int(h) / int(CELL));
        int x = std::rand() % cols;
        int y = std::rand() % rows;
        m_food.setPosition({float(x * CELL + CELL / 2), float(y * CELL + CELL / 2)});
    }

    void Food::draw(sf::RenderTarget &rt) const
    {
        rt.draw(m_food);
    }

    sf::FloatRect Food::bounds() const
    {
        return m_food.getGlobalBounds();
    }
}
