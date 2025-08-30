#pragma once
#include <SFML/Graphics.hpp>

namespace Snake
{
    constexpr unsigned WINDOW_W = 1920;
    constexpr unsigned WINDOW_H = 1080;
    constexpr unsigned CELL = 60;

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
