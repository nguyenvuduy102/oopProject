#pragma once
#include "../../../GameMain/Core/include/IGame.h"
#include "GameCore.h"
#include "GameRenderer.h"

namespace Pong
{
    class PongGame : public IGame
    {
    public:
        PongGame();
        void init(sf::RenderWindow &window) override;
        void run(sf::RenderWindow &window) override;
        void cleanup() override;
        std::string name() const override { return "Pong"; }

    private:
        GameCore m_core;
        GameRenderer m_renderer;
    };
}
