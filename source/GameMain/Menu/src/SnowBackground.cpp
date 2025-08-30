/**
 * @file SnowBackground.cpp
 * @brief Implements the SnowBackground class methods for animated snow effects.
 */

#include "../include/SnowBackground.h"
#include <cstdint>

/**
 * @brief Constructs a SnowBackground object and initializes snowflakes.
 * @param window Reference to the SFML render window.
 * @param count Number of snowflakes.
 */
SnowBackground::SnowBackground(sf::RenderWindow &window, int count)
    : m_window(window), m_topColor(20, 20, 40), m_rng(std::random_device{}())
{
    std::uniform_real_distribution<float> distX(0.f, (float)window.getSize().x);
    std::uniform_real_distribution<float> distY(0.f, (float)window.getSize().y);
    std::uniform_real_distribution<float> distSpeed(30.f, 80.f);

    for (int i = 0; i < count; i++)
    {
        Snowflake s;
        s.shape = sf::CircleShape(2.f);
        s.shape.setFillColor(sf::Color::White);
        s.shape.setPosition({distX(m_rng), distY(m_rng)});
        s.speed = distSpeed(m_rng);
        m_snowflakes.push_back(s);
    }
}

/**
 * @brief Updates and draws the animated snow background.
 * @param dt Delta time in seconds.
 */
void SnowBackground::update(float dt)
{
    // vẽ gradient nền
    sf::VertexArray grad(sf::PrimitiveType::TriangleStrip, 4);
    grad[0].position = {0.f, 0.f};
    grad[1].position = {(float)m_window.getSize().x, 0.f};
    grad[2].position = {0.f, (float)m_window.getSize().y};
    grad[3].position = {(float)m_window.getSize().x, (float)m_window.getSize().y};

    grad[0].color = grad[1].color = m_topColor;
    grad[2].color = grad[3].color =
        sf::Color((std::uint8_t)(m_topColor.r * 0.3f + 60),
                  (std::uint8_t)(m_topColor.g * 0.3f + 80),
                  (std::uint8_t)(m_topColor.b * 0.3f + 150));

    m_window.draw(grad);

    // cập nhật và vẽ tuyết
    // cập nhật và vẽ tuyết
    for (auto &s : m_snowflakes)
    {
        s.shape.move(sf::Vector2f(0.f, s.speed * dt)); // ⬅ sửa
        if (s.shape.getPosition().y > m_window.getSize().y)
        {
            s.shape.setPosition(
                {s.shape.getPosition().x, -5.f}); // reset lại trên đầu
        }
        m_window.draw(s.shape);
    }
}
