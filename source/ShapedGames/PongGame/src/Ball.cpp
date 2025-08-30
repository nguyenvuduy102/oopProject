#include "../include/Ball.h"
#include <random>

namespace Pong
{
    Ball::Ball(float radius)
    {
        m_shape.setRadius(radius);
        m_shape.setFillColor(sf::Color::White);
        m_shape.setOrigin({radius, radius});
        m_velocity = {0.f, 0.f};
    }

    void Ball::reset(const sf::Vector2u &windowSize, int direction)
    {
        m_shape.setPosition({windowSize.x / 2.f, windowSize.y / 2.f});
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> dy(3.5f, 5.0f);
        float vy = dy(gen);
        m_velocity = {direction > 0 ? 15.f : -15.f, (gen() % 2 == 0) ? vy : -vy};
    }

    void Ball::update()
    {
        m_shape.move(m_velocity);
    }

    void Ball::invertX()
    {
        m_velocity.x = -m_velocity.x;
    }

    void Ball::invertY()
    {
        m_velocity.y = -m_velocity.y;
    }

    void Ball::setVelocity(const sf::Vector2f &vel)
    {
        m_velocity = vel;
    }
}
