#include "../include/TetrisGame.h"

namespace Tetris
{
    TetrisGame::TetrisGame()
        : core(), audio(), renderer(nullptr), controller(nullptr) {}

    void TetrisGame::init(sf::RenderWindow &window)
    {
        if (!font.openFromFile("../source/assets/fonts/stawix-sansbeamhead-semibold.otf"))
        {
            throw std::runtime_error("Không load được font!");
        }
        renderer = new GameRenderer(font, "../source/assets/images/TetrisSprite.png");
        controller = new GameController(core, audio, *renderer);
        audio.PlayMusic();
    }

    void TetrisGame::run(sf::RenderWindow &window)
    {
        // === COUNTDOWN ===
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));

        sf::Text countdownText(font, "3", 72);
        countdownText.setFillColor(sf::Color::White);

        sf::Clock clock;
        int count = 3;

        while (count > 0 && window.isOpen())
        {
            while (auto ev = window.pollEvent())
            {
                if (ev->is<sf::Event::Closed>())
                    window.close();
            }

            float elapsed = clock.getElapsedTime().asSeconds();
            if (elapsed >= 1.f)
            {
                count--;
                clock.restart();
            }

            window.clear(darkLight);
            controller->Render(window);
            window.draw(overlay);

            if (count > 0)
                countdownText.setString(std::to_string(count));
            else
                countdownText.setString("GO!");

            // căn giữa text
            sf::FloatRect bounds = countdownText.getLocalBounds();
            countdownText.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
            countdownText.setPosition(
                {(float)window.getSize().x / 2.f, (float)window.getSize().y / 2.f});

            window.draw(countdownText);
            window.display();
        }

        sf::Clock dropClock;
        while (window.isOpen())
        {
            while (auto ev = window.pollEvent())
            {
                if (ev->is<sf::Event::Closed>())
                    window.close();
                if (auto key = ev->getIf<sf::Event::KeyPressed>())
                    if (key->code == sf::Keyboard::Key::Escape)
                        return;
            }

            controller->HandleInput(window);

            if (!controller->IsPaused() && !core.IsGameOver())
            {
                if (dropClock.getElapsedTime().asSeconds() > 0.5f)
                {
                    auto res = core.MoveDown();
                    if (res.rowsCleared > 0)
                        audio.PlayClear();
                    if (res.gameOver)
                    {
                        audio.StopMusic();
                        audio.PlayGameOver();
                    }
                    dropClock.restart();
                }
            }

            window.clear(lightGray);

            controller->Render(window);

            window.display();
        }
    }

    void TetrisGame::cleanup()
    {
        delete renderer;
        delete controller;
        renderer = nullptr;
        controller = nullptr;
    }
}
