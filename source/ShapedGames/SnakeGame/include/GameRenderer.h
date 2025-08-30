#pragma once
#include <SFML/Graphics.hpp>
#include "GameController.h"

namespace Snake
{
    class GameRenderer
    {
    public:
        GameRenderer(sf::RenderWindow &window);
        void render(const GameController &controller);

        private : sf::RenderWindow &m_window;
        sf::Font m_font;
    };
}
