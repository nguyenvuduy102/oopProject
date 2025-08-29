#pragma once
#include "GameCore.h"
#include "AudioManager.h"
#include "GameRenderer.h"
#include <SFML/Graphics.hpp>

namespace Tetris
{
    class GameController
    {
    public:
        GameController(GameCore &core, AudioManager &audio, GameRenderer &renderer);
        void HandleInput(sf::RenderWindow &window);
        void Update();
        void Render(sf::RenderWindow &window);
        int GetGameOverChoice() const { return gameOverChoice; }
        bool IsPaused() const { return paused; }

    private:
        GameCore &core;
        AudioManager &audio;
        GameRenderer &renderer;

        sf::Clock inputClock;
        float moveDelay = 0.15f;
        int gameOverChoice = 0;
        bool paused = false;
        bool prevP = false;
        bool prevLeft = false;
        bool prevRight = false;
        bool prevEnter = false;
    };
}
