#pragma once
#include "../../../GameMain/Core/include/BaseGame.h"
#include "GameCore.h"
#include "GameRenderer.h"
#include "GameController.h"
#include "AudioManager.h"
#include <SFML/Graphics.hpp>

namespace Tetris
{
    class TetrisGame : public IGame
    {
    public:
        TetrisGame();
        void init(sf::RenderWindow &window) override;
        void run(sf::RenderWindow &window) override;
        void cleanup() override;
        std::string name() const override { return "Tetris"; }

    private:
        GameCore core;
        AudioManager audio;
        sf::Font font;
        GameRenderer *renderer;
        GameController *controller;
    };
}
