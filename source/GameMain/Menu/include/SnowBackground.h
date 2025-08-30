#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

// Struct for a single snowflake
struct Snowflake
{
    sf::CircleShape shape; // Circle shape for snowflake
    float speed;           // How fast it fall
};

// SnowBackground class, make snowy effect for background
class SnowBackground
{
public:
    // Constructor, set up snow with window and number of flakes
    SnowBackground(sf::RenderWindow &window, int count = 100);

    // Update and draw the snowy background
    void update(float dt);

private:
    sf::RenderWindow &m_window;          // Ref to SFML window
    std::vector<Snowflake> m_snowflakes; // List of snowflakes
    sf::Color m_topColor;                // Top color for gradient
    sf::Clock m_clock;                   // Clock for timing
    std::mt19937 m_rng;                  // Random number generator
};