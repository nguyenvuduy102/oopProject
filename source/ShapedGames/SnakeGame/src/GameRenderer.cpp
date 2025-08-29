#include "../include/GameRenderer.h"
#include <iostream>

namespace Snake
{
    GameRenderer::GameRenderer(sf::RenderWindow &window) : m_window(window)
    {
        if (!m_font.openFromFile("assets/fonts/JetBrainsMono-Medium.ttf"))
        {
            std::cerr << "Warning: cannot load font\n";
        }
    }

    void GameRenderer::render(const GameController &controller)
    {
        m_window.clear(sf::Color(12, 12, 12));
        auto mode = controller.mode();

        if (mode == Mode::Menu)
        {
            sf::Text title(m_font, "Snake (SFML 3)", 48);
            title.setFillColor(sf::Color::White);
            auto ws = m_window.getSize();
            auto tb = title.getLocalBounds();
            title.setOrigin({tb.position.x + tb.size.x / 2.f, tb.position.y + tb.size.y / 2.f});
            title.setPosition({float(ws.x) / 2.f, 80.f});
            m_window.draw(title);

            sf::Text info(m_font, "Press 1 (1P)   Press 2 (2P)\nEsc to quit", 22);
            info.setFillColor(sf::Color::White);
            info.setPosition({120.f, 160.f});
            m_window.draw(info);
        }
        else if (mode == Mode::OnePlayer)
        {
            controller.food().draw(m_window);
            controller.player1().draw(m_window);

            sf::Text s(m_font, "Score: " + std::to_string(controller.score1()), 20);
            s.setFillColor(sf::Color::White);
            s.setPosition({8.f, 8.f});
            m_window.draw(s);
        }
        else if (mode == Mode::TwoPlayers)
        {
            controller.food().draw(m_window);
            controller.player1().draw(m_window);
            controller.player2().draw(m_window);

            sf::Text s1(m_font, "P1: " + std::to_string(controller.score1()), 18);
            sf::Text s2(m_font, "P2: " + std::to_string(controller.score2()), 18);
            s1.setFillColor(sf::Color::White);
            s2.setFillColor(sf::Color::White);
            s1.setPosition({8.f, 8.f});
            s2.setPosition({8.f, 28.f});
            m_window.draw(s1);
            m_window.draw(s2);
        }
        else if (mode == Mode::GameOver)
        {
            auto ws = m_window.getSize();

            sf::Text go(m_font, "Game Over", 48);
            go.setFillColor(sf::Color::Red);
            auto gb = go.getLocalBounds();
            go.setOrigin({gb.position.x + gb.size.x / 2.f, gb.position.y + gb.size.y / 2.f});
            go.setPosition({float(ws.x) / 2.f, float(ws.y) / 2.f - 20.f});
            m_window.draw(go);

            sf::Text info(m_font, "Press Esc to return to menu", 24);
            info.setFillColor(sf::Color::White);
            info.setPosition({float(ws.x) / 2.f - 140.f, float(ws.y) / 2.f + 30.f});
            m_window.draw(info);
        }

        m_window.display();
    }

}