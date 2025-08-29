#pragma once
#include <SFML/Graphics.hpp>

namespace Pong
{
    class Paddle
    {
    public:
        Paddle(const sf::Vector2f &size, const sf::Vector2f &pos, float speed);
        void moveUp();
        void moveDown();
        void updateBounds(const sf::Vector2u &windowSize);
        const sf::RectangleShape &shape() const { return m_shape; }
        sf::RectangleShape &shape() { return m_shape; }
        sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }
        void setPosition(const sf::Vector2f &pos) { m_shape.setPosition(pos); }

    private:
        sf::RectangleShape m_shape;
        float m_speed;
    };
}
