// GameRenderer.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Pipe.h"
#include "TextureManager.h"
#include "GameCore.h"
#include <array>

namespace Flappy
{
    class GameRenderer
    {
    public:
        GameRenderer(TextureManager &tex);
        void load();
        void render(sf::RenderWindow &window,
                    const Bird &bird,
                    const std::deque<Pipe> &pipes,
                    int score,
                    GameState state,
                    int frames);

    private:
        TextureManager &m_textures;
        sf::Font m_font;
        sf::Text m_scoreText;
        std::array<sf::Sprite, 6> m_background; // ✅ std::array thay cho raw array
        sf::Sprite m_gameover;
        sf::Text m_pressC;
    };
}
