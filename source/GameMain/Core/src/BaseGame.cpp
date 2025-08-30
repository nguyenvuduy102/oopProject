
/**
 * @file BaseGame.cpp
 * @brief Implements the BaseGame class methods.
 */

#include "../include/BaseGame.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/// Path to the font file used in the game.
static const char *FONT_PATH = "assets/fonts/monogram.ttf";

/**
 * @brief Constructs a BaseGame object.
 * @param n Name of the game.
 * @param bg Background color.
 */
BaseGame::BaseGame(const std::string &n, sf::Color bg) : m_name(n), m_bg(bg) {}

/**
 * @brief Initializes the game. (Empty for base implementation)
 * @param window Reference to the SFML render window.
 */
void BaseGame::init(sf::RenderWindow &) {}

/**
 * @brief Runs the main game loop, displays game name and handles ESC to exit.
 * @param window Reference to the SFML render window.
 */
void BaseGame::run(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.openFromFile(FONT_PATH))
    {
        throw std::runtime_error("Cannot load font from " + std::string(FONT_PATH));
    }

    sf::Text text(font, sf::String(m_name + " - Press ESC to return"), 24);
    text.setPosition({40.f, 40.f});

    while (window.isOpen())
    {
        while (auto evOpt = window.pollEvent())
        {
            const sf::Event &ev = *evOpt;
            if (ev.is<sf::Event::Closed>())
            {
                window.close();
                return;
            }
            if (auto key = ev.getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                    return;
            }
        }
        window.clear(m_bg);
        window.draw(text);
        window.display();
    }
}

/**
 * @brief Cleans up resources used by the game. (Empty for base implementation)
 */
void BaseGame::cleanup() {}

/**
 * @brief Gets the name of the game.
 * @return Name as a string.
 */
std::string BaseGame::name() const { return m_name; }
