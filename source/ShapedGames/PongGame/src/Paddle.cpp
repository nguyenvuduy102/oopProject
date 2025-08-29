#include "../include/Paddle.h"

namespace Pong
{
    Paddle::Paddle(const sf::Vector2f &size, const sf::Vector2f &pos, float speed)
        : m_speed(speed)
    {
        m_shape.setSize(size);
        m_shape.setFillColor(sf::Color::White);
        m_shape.setPosition(pos);
    }

    void Paddle::moveUp()
    {
        m_shape.move({0.f, -m_speed});
    }

    void Paddle::moveDown()
    {
        m_shape.move({0.f, m_speed});
    }

    void Paddle::updateBounds(const sf::Vector2u &windowSize)
    {
        if (m_shape.getPosition().y < 0.f)
            m_shape.setPosition({m_shape.getPosition().x, 0.f});
        if (m_shape.getPosition().y + m_shape.getSize().y > windowSize.y)
            m_shape.setPosition({m_shape.getPosition().x, windowSize.y - m_shape.getSize().y});
    }
}
