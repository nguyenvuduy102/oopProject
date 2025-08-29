#pragma once
#include <SFML/Graphics.hpp>

namespace Snake
{
    constexpr unsigned WINDOW_W = 800;
    constexpr unsigned WINDOW_H = 600;
    constexpr unsigned CELL = 40;

    class Food
    {
    public:
        Food();
        void spawn(unsigned w, unsigned h);
        void draw(sf::RenderTarget &rt) const;
        sf::FloatRect bounds() const;

    private:
        sf::CircleShape m_food;
    };
}
