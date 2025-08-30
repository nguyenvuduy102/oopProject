#include "../include/SnowBackground.h"
#include <cstdint>

// Set up snowy background effect with given window and snowflake count
SnowBackground::SnowBackground(sf::RenderWindow &window, int count)
    : m_window(window), m_topColor(20, 20, 40), m_rng(std::random_device{}()) // Init window, top color, and random generator
{
    // Make random ranges for snowflake position and speed
    std::uniform_real_distribution<float> distX(0.f, (float)window.getSize().x); // Random x
    std::uniform_real_distribution<float> distY(0.f, (float)window.getSize().y); // Random y 
    std::uniform_real_distribution<float> distSpeed(30.f, 80.f);                 // Random speed for falling

    // Create snowflakes
    for (int i = 0; i < count; i++) // Loop to make all snowflakes
    {
        Snowflake s;                                       // snowflake
        s.shape = sf::CircleShape(2.f);                    // circle
        s.shape.setFillColor(sf::Color::White);            // Make it white so it look like snow
        s.shape.setPosition({distX(m_rng), distY(m_rng)}); // Put it at random spot
        s.speed = distSpeed(m_rng);                        // Give random fall speed
        m_snowflakes.push_back(s);                         // Add to list
    }
}

// Update and draw background with gradient and snowflakes
void SnowBackground::update(float dt)
{
    // Draw gradient background
    sf::VertexArray grad(sf::PrimitiveType::TriangleStrip, 4);                     // Make triangle strip for gradient
    grad[0].position = {0.f, 0.f};                                                 // Top-left corner
    grad[1].position = {(float)m_window.getSize().x, 0.f};                         // Top-right corner
    grad[2].position = {0.f, (float)m_window.getSize().y};                         // Bottom-left corner
    grad[3].position = {(float)m_window.getSize().x, (float)m_window.getSize().y}; // Bottom-right corner

    grad[0].color = grad[1].color = m_topColor; // Set top color for gradient
    grad[2].color = grad[3].color =             // Set bottom color, bit brighter
        sf::Color((std::uint8_t)(m_topColor.r * 0.3f + 60),
                  (std::uint8_t)(m_topColor.g * 0.3f + 80),
                  (std::uint8_t)(m_topColor.b * 0.3f + 150));

    m_window.draw(grad); // Draw the gradient

    // Update and draw snowflakes
    for (auto &s : m_snowflakes) // Loop through all snowflakes
    {
        s.shape.move(sf::Vector2f(0.f, s.speed * dt));      // Move snowflake down based on speed
        if (s.shape.getPosition().y > m_window.getSize().y) // If snowflake go off bottom
        {
            s.shape.setPosition({s.shape.getPosition().x, -5.f}); // Reset to top
        }
        m_window.draw(s.shape); // Draw snowflake
    }
}