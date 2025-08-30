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

    void GameRenderer::Draw(sf::RenderWindow &window, GameCore &core, int choice, bool paused)
    {
        if (hasBackground)
            window.draw(*bgSprite); // vẽ nền PNG

        core.GetGrid().Draw(window);
        core.GetCurrentBlock().Draw(window, LEFT_OFFSET, TOP_OFFSET);

        DrawUI(window, core, choice, paused);
        DrawNext(window, core.GetNextBlock());
    }

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

        // Đặt Next block ở góc phải trên
        int boxSize = 200;
        int ox = winSize.x - boxSize - 50; // cách mép phải 50px
        int oy = 50;                       // cách mép trên 50px

        auto colors = GetCellColors();
        for (auto &p : cells)
        {
            sf::RectangleShape cell({(float)CELL - 2, (float)CELL - 2});
            cell.setPosition({(float)(ox + (p.column - minC) * CELL - 570.f),
                              (float)(oy + (p.row - minR) * CELL + 250.f)});

            cell.setFillColor(colors[block.id]);
            cell.setOutlineThickness(1.f);
            cell.setOutlineColor(sf::Color::Black);
            window.draw(cell);
        }
    }

    void GameRenderer::DrawUI(sf::RenderWindow &window, GameCore &core, int choice, bool paused)
    {
        sf::Vector2u winSize = window.getSize();

        auto drawVal = [&](const char *label, int val, float y)
        {
            char buf[32];
            std::snprintf(buf, sizeof(buf), "%d", val);
            sf::Text t(font, buf, 32);
            t.setFillColor(sf::Color::White);

            sf::FloatRect bounds = t.getLocalBounds();
            t.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                         bounds.position.y});

            // Đặt cột thông tin ở gần mép phải
            t.setPosition({winSize.x - 770.f, y + 200.f});
            window.draw(t);
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
