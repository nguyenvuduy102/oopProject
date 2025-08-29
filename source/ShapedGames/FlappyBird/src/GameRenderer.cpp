#include "../include/GameRenderer.h"
#include <stdexcept>

namespace Flappy
{
    GameRenderer::GameRenderer(TextureManager &tex)
        : m_textures(tex),
          m_scoreText(m_font, "", 40),
          m_pressC(m_font, "Press C to continue", 30),
          m_background{
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground())},
          m_gameover(tex.getGameover())
    {
    }

    void GameRenderer::load()
    {
        if (!m_font.openFromFile("assets/fonts/flappy.ttf"))
            throw std::runtime_error("failed to load flappy.ttf");

        for (int i = 0; i < 6; ++i)
        {
            m_background[i].setScale({2.0f, 2.0f});
            m_background[i].setPosition({i * 266.f, 0.f});
        }

        m_gameover.setOrigin({96.f, 21.f});
        m_gameover.setPosition({400.f, 200.f});
        m_gameover.setScale({2.f, 2.f});

        m_scoreText.setFillColor(sf::Color::White);
        m_scoreText.setPosition({20.f, 10.f});

        m_pressC.setFillColor(sf::Color::White);
        sf::FloatRect bounds = m_pressC.getLocalBounds();
        m_pressC.setOrigin({bounds.size.x / 2.f, 0.f});
        m_pressC.setPosition({400.f, 300.f});
    }

    void GameRenderer::render(sf::RenderWindow &window,
                              const Bird &bird,
                              const std::deque<Pipe> &pipes,
                              int score,
                              GameState state,
                              int frames)
    {
        window.clear();

        for (auto &bg : m_background)
            window.draw(bg);

        for (auto &pipe : pipes)
        {
            window.draw(pipe.upper());
            window.draw(pipe.lower());
        }

        window.draw(bird.sprite());

        m_scoreText.setString(std::to_string(score));
        window.draw(m_scoreText);

        if (state == GameState::Gameover)
        {
            window.draw(m_gameover);
            if (frames % 60 < 30)
                window.draw(m_pressC);
        }

        window.display();
    }
}
