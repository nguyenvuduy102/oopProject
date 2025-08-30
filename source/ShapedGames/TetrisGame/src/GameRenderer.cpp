#include "../include/GameRenderer.h"
#include "../include/GameController.h"
#include "../include/colors.h"
#include <algorithm>
#include <cstdio>
#include <iostream>

namespace Tetris
{
    static constexpr int CELL = 30;
    static constexpr int LEFT_OFFSET = 12;
    static constexpr int TOP_OFFSET = -10;

    /**
     * @brief Constructs a GameRenderer with a font and optional background image.
     * @param f The SFML font for text rendering.
     * @param bgPath Path to the background image (optional).
     */
    GameRenderer::GameRenderer(sf::Font &f, const std::string &bgPath)
        : font(f)
    {
        if (!bgPath.empty() && bgTexture.loadFromFile(bgPath))
        {
            hasBackground = true;
            bgSprite = std::make_unique<sf::Sprite>(bgTexture);

            // Scale nền theo chiều cao cửa sổ
            float scaleX = 1.f;
            float scaleY = 1080.f / bgTexture.getSize().y; // sửa: 1080 (màn hình thật)
            float scale = std::min(scaleX, scaleY);
            bgSprite->setScale({scale, scale});

            // Căn giữa nền theo cửa sổ hiện tại
            float spriteW = bgTexture.getSize().x * scale;
            float spriteH = bgTexture.getSize().y * scale;
            bgSprite->setPosition({(1920.f - spriteW) / 2.f,
                                   (1080.f - spriteH) / 2.f});
        }
    }

    /**
     * @brief Draws the entire game scene, including grid, blocks, and UI.
     * @param window The SFML render window.
     * @param core The GameCore providing game state.
     * @param choice The user's choice in the game over menu (0 for YES, 1 for NO).
     * @param paused True if the game is paused.
     */
    void GameRenderer::Draw(sf::RenderWindow &window, GameCore &core, int choice, bool paused)
    {
        if (hasBackground)
            window.draw(*bgSprite); // vẽ nền PNG

        core.GetGrid().Draw(window);
        core.GetCurrentBlock().Draw(window, LEFT_OFFSET, TOP_OFFSET);

        DrawUI(window, core, choice, paused);
        DrawNext(window, core.GetNextBlock());
    }

    /**
     * @brief Draws the next block preview.
     * @param window The SFML render window.
     * @param block The next Block to draw.
     */
    void GameRenderer::DrawNext(sf::RenderWindow &window, const Block &block)
    {
        sf::Vector2u winSize = window.getSize();
        auto cells = block.GetRawCellPositions();

        int minR = 99, maxR = -99, minC = 99, maxC = -99;
        for (auto &p : cells)
        {
            minR = std::min(minR, p.row);
            maxR = std::max(maxR, p.row);
            minC = std::min(minC, p.column);
            maxC = std::max(maxC, p.column);
        }

        int bw = (maxC - minC + 1) * CELL;
        int bh = (maxR - minR + 1) * CELL;

        sf::Text text(font, "Next", 32);
        text.setFillColor(sf::Color::White);
        text.setPosition({winSize.x / 2.f + 200.f, winSize.y / 2.f - 100.f});
        window.draw(text);

        for (auto &p : cells)
        {
            sf::RectangleShape cell({(float)CELL - 2, (float)CELL - 2});
            cell.setFillColor(GetCellColors()[block.id]);
            cell.setPosition({winSize.x / 2.f + 200.f + (p.column - minC) * CELL,
                              winSize.y / 2.f - 100.f + (p.row - minR) * CELL + 50.f});
            window.draw(cell);
        }
    }

    /**
     * @brief Draws the user interface elements like score, lines, level, pause overlay, and game over menu.
     * @param window The SFML render window.
     * @param core The GameCore providing game data.
     * @param choice The user's choice in the game over menu.
     * @param paused True if the game is paused.
     */
    void GameRenderer::DrawUI(sf::RenderWindow &window, GameCore &core, int choice, bool paused)
    {
        sf::Vector2u winSize = window.getSize();

        auto drawVal = [&](const std::string &label, int val, float y)
        {
            sf::Text lbl(font, label, 32);
            lbl.setFillColor(sf::Color::White);
            lbl.setPosition({winSize.x / 2.f - 200.f, y});
            window.draw(lbl);

            sf::Text v(font, std::to_string(val), 32);
            v.setFillColor(sf::Color::White);
            v.setPosition({winSize.x / 2.f - 100.f, y});
            window.draw(v);
        };

        drawVal("Score", core.GetScore(), 300.f);
        drawVal("Line", core.GetLines(), 400.f);
        drawVal("Level", core.GetLevel(), 500.f);

        if (paused)
        {
            sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(overlay);

            sf::Text pause(font, "Please press P again to return", 28);
            pause.setFillColor(sf::Color::White);
            sf::FloatRect pb = pause.getLocalBounds();
            pause.setOrigin({pb.size.x / 2.f, pb.size.y / 2.f});
            pause.setPosition({winSize.x / 2.f, winSize.y / 2.f});
            window.draw(pause);
        }

        if (core.IsGameOver())
        {
            sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
            overlay.setFillColor(sf::Color(0, 0, 0, 180));
            window.draw(overlay);

            sf::Text title(font, "GAME OVER", 64);
            title.setFillColor(sf::Color::White);
            sf::FloatRect tb = title.getLocalBounds();
            title.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
            title.setPosition({winSize.x / 2.f, 200.f});
            window.draw(title);

            sf::Text play(font, "PLAY AGAIN", 32);
            play.setFillColor(sf::Color::White);
            sf::FloatRect pb = play.getLocalBounds();
            play.setOrigin({pb.size.x / 2.f, pb.size.y / 2.f});
            play.setPosition({winSize.x / 2.f, 300.f});
            window.draw(play);

            sf::Text yes(font, "YES", 28);
            sf::Text no(font, "NO", 28);

            yes.setPosition({winSize.x / 2.f - 60.f, 400.f});
            no.setPosition({winSize.x / 2.f + 20.f, 400.f});

            if (choice == 0)
            {
                yes.setFillColor(sf::Color::Yellow);
                no.setFillColor(sf::Color::White);
            }
            else
            {
                yes.setFillColor(sf::Color::White);
                no.setFillColor(sf::Color::Yellow);
            }

            window.draw(yes);
            window.draw(no);
        }
    }
}