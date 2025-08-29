#include "../include/GameController.h"
#include <SFML/Window/Keyboard.hpp>

namespace Tetris
{
    GameController::GameController(GameCore &c, AudioManager &a, GameRenderer &r)
        : core(c), audio(a), renderer(r) {}

    void GameController::HandleInput(sf::RenderWindow &window)
    {
        // ===== Game Over Menu =====
        if (core.IsGameOver())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) && !prevLeft)
                gameOverChoice = 1 - gameOverChoice;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) && !prevRight)
                gameOverChoice = 1 - gameOverChoice;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter) && !prevEnter)
            {
                if (gameOverChoice == 0) // YES
                {
                    core.Reset();
                    audio.PlayMusic();
                }
                else
                {
                    window.close();
                }
            }

            prevLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left);
            prevRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right);
            prevEnter = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter);
            return;
        }

        // ===== Pause =====
        bool curP = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P);
        if (curP && !prevP)
        {
            paused = !paused;
            if (paused)
            {
                audio.PauseMusic();
            }
            else
            {
                audio.ResumeMusic();
            }
        }
        prevP = curP;

        if (paused)
            return;

        const float elapsed = inputClock.getElapsedTime().asSeconds();
        if (elapsed < moveDelay)
            return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
        {
            core.MoveLeft();
            inputClock.restart();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
        {
            core.MoveRight();
            inputClock.restart();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
        {
            auto res = core.MoveDown();
            if (res.rowsCleared > 0)
                audio.PlayClear();
            if (res.gameOver)
            {
                audio.StopMusic();
                audio.PlayGameOver();
            }
            inputClock.restart();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
        {
            if (core.Rotate())
                audio.PlayRotate();
            inputClock.restart();
        }
    }

    void GameController::Update()
    {
    }

    void GameController::Render(sf::RenderWindow &window)
    {
        renderer.Draw(window, core, gameOverChoice, paused);
    }
}
