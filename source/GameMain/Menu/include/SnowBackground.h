
/**
 * @file SnowBackground.h
 * @brief Declares the SnowBackground class for animated snow effects.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

/**
 * @struct Snowflake
 * @brief Represents a single snowflake in the background.
 */
struct Snowflake
{
    sf::CircleShape shape; /**< Shape of the snowflake. */
    float speed;           /**< Falling speed of the snowflake. */
};

/**
 * @class SnowBackground
 * @brief Handles animated snow background effects.
 */
class SnowBackground
{
public:
    /**
     * @brief Constructs a SnowBackground object.
     * @param window Reference to the SFML render window.
     * @param count Number of snowflakes.
     */
    SnowBackground(sf::RenderWindow &window, int count = 100);

    /**
     * @brief Updates and draws the animated snow background.
     * @param dt Delta time in seconds.
     */
    void update(float dt);

private:
    sf::RenderWindow &m_window;           /**< Reference to the render window. */
    std::vector<Snowflake> m_snowflakes;  /**< List of snowflakes. */
    sf::Color m_topColor;                 /**< Color at the top of the background. */
    sf::Clock m_clock;                    /**< Clock for timing snow updates. */
    std::mt19937 m_rng;                   /**< Random number generator for snowflakes. */
};
