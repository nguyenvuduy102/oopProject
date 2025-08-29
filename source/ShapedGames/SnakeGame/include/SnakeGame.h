#pragma once
#include "../../../GameMain/Core/include/IGame.h"
#include "GameRenderer.h"
#include "GameController.h"
#include "AudioManager.h"

namespace Snake
{
    class SnakeGame : public IGame
    {
    public:
        SnakeGame();

        void init(sf::RenderWindow &window) override;
        void run(sf::RenderWindow &window) override;
        void cleanup() override;
        std::string name() const override { return "Snake"; }

    private:
        GameRenderer *m_renderer{nullptr};
        AudioManager m_audio;
        GameController m_controller;
        bool m_initialized{false};
    };
}