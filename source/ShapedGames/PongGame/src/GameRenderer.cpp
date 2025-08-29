#include "../include/GameRenderer.h"

namespace Pong
{
    GameRenderer::GameRenderer() : m_scoreText(m_font, "", 28) {}

    void GameRenderer::load()
    {
        if (!m_font.openFromFile("assets/fonts/monogram.ttf"))
            throw std::runtime_error("Failed to load font: assets/fonts/monogram.ttf");
        m_scoreText.setFillColor(sf::Color::White);
    }

    void GameRenderer::render(sf::RenderWindow &window,
                              const Paddle &left,
                              const Paddle &right,
                              const Ball &ball,
                              int leftScore,
                              int rightScore)
    {
        window.clear(sf::Color(20, 20, 20));
        window.draw(left.shape());
        window.draw(right.shape());
        window.draw(ball.shape());

        m_scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
        m_scoreText.setPosition({window.getSize().x / 2.f - 40.f, 20.f});
        window.draw(m_scoreText);

        window.display();
    }
}
