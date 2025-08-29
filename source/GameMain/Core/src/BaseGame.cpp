#include "../include/BaseGame.h"
#include <SFML/Graphics.hpp>
#include <iostream>

static const char *FONT_PATH = "assets/fonts/monogram.ttf";

BaseGame::BaseGame(const std::string &n, sf::Color bg) : m_name(n), m_bg(bg) {}

void BaseGame::init(sf::RenderWindow &) {}

void BaseGame::run(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.openFromFile(FONT_PATH))
    {
        throw std::runtime_error("Không load được font từ " + std::string(FONT_PATH));
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

void BaseGame::cleanup() {}
std::string BaseGame::name() const { return m_name; }
