#pragma once
#include <SFML/Graphics.hpp>

namespace Pong
{
    class Ball
    {
    public:
        Ball(float radius = 10.f);
        void reset(const sf::Vector2u &windowSize, int direction);
        void update();
        void invertX();
        void invertY();
        void setVelocity(const sf::Vector2f &vel);
        const sf::CircleShape &shape() const { return m_shape; }
        sf::CircleShape &shape() { return m_shape; }
        sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }
        sf::Vector2f getPosition() const { return m_shape.getPosition(); }
        void setPosition(const sf::Vector2f &pos) { m_shape.setPosition(pos); }

    private:
        sf::CircleShape m_shape;
        sf::Vector2f m_velocity;
    };
}
