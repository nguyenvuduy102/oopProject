#pragma once // Stop multiple includes
#include "../../../GameMain/Core/include/IGame.h"
#include "GameCore.h"
#include "GameRenderer.h"
#include "TextureManager.h"

namespace Flappy
{
    // FlappyGame class, main class for Flappy Bird
    class FlappyGame : public IGame
    {
    public:
        // Constructor, set up game
        FlappyGame();
        // Init game with window
        void init(sf::RenderWindow &window) override;
        // Run game loop
        void run(sf::RenderWindow &window) override;
        // Clean up game stuff
        void cleanup() override;
        // Get game name
        std::string name() const override { return "Flappy Bird"; }

    private:
        TextureManager m_textures; // Manage textures
        GameCore *m_core;          // Game logic
        GameRenderer *m_renderer;  // Game rendering
    };
}