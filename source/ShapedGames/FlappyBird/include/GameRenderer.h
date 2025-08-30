// GameRenderer.h
#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Pipe.h"
#include "TextureManager.h"
#include "GameCore.h"
#include <array>

namespace Flappy
{
    // GameRenderer class, draw game stuff to window
    class GameRenderer
    {
    public:
        // Constructor, take texture manager
        GameRenderer(TextureManager &tex);
        // Load fonts and textures
        void load();
        // Draw bird, pipes, score, and gameover stuff
        void render(sf::RenderWindow &window,
                    const Bird &bird,
                    const std::deque<Pipe> &pipes,
                    int score,
                    GameState state,
                    int frames);

    private:
        TextureManager &m_textures;             // Texture manager ref
        sf::Font m_font;                        // Font for score text
        sf::Text m_scoreText;                   // Text for showing score
        std::array<sf::Sprite, 6> m_background; // Array of background sprites
        sf::Sprite m_gameover;                  // Game over image
        sf::Text m_pressC;                      // Text for "press C" prompt
    };
}