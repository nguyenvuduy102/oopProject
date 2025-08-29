#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

struct Snowflake
{
    sf::CircleShape shape;
    float speed;
};

class SnowBackground
{
public:
    SnowBackground(sf::RenderWindow &window, int count = 100);

    // cập nhật và vẽ nền động
    void update(float dt);

private:
    sf::RenderWindow &m_window;
    std::vector<Snowflake> m_snowflakes;
    sf::Color m_topColor;
    sf::Clock m_clock;
    std::mt19937 m_rng;
};
