#pragma once
#include "../../../GameMain/Core/include/IGame.h"
#include "GameCore.h"
#include "GameRenderer.h"
#include "TextureManager.h"

namespace Flappy
{
    class FlappyGame : public IGame
    {
    public:
        FlappyGame();
        void init(sf::RenderWindow &window) override;
        void run(sf::RenderWindow &window) override;
        void cleanup() override;
        std::string name() const override { return "Flappy Bird"; }

    private:
        TextureManager m_textures;
        GameCore *m_core;
        GameRenderer *m_renderer;
    };
}
