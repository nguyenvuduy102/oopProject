#pragma once
#include <SFML/Graphics.hpp>
#include "GameCore.h"

namespace Tetris
{
    class GameRenderer
    {
    public:
        GameRenderer(sf::Font &font, const std::string &bgPath);
        void Draw(sf::RenderWindow &window, GameCore &core, int choice, bool paused);
        void DrawNext(sf::RenderWindow &window, const Block &next);

    private:
        sf::Font &font;
        sf::Texture bgTexture;
        std::unique_ptr<sf::Sprite> bgSprite;
        bool hasBackground = false;

        void DrawUI(sf::RenderWindow &window, GameCore &core, int choice, bool paused);
    };
}
