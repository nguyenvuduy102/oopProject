#include "../include/GameCore.h"

namespace Pong
{
    GameCore::GameCore()
        : m_left({12.f, 90.f}, {20.f, 200.f}, 6.5f),
          m_right({12.f, 90.f}, {760.f, 200.f}, 6.5f),
          m_ball(10.f),
          m_leftScore(0),
          m_rightScore(0)
    {
    }

    void GameCore::init(const sf::Vector2u &windowSize)
    {
        m_audio.load();
        resetBall(windowSize, 1);
    }

    void GameCore::update(const sf::Vector2u &windowSize)
    {
        m_ball.update();
        m_left.updateBounds(windowSize);
        m_right.updateBounds(windowSize);

        if (m_ball.getBounds().findIntersection(m_left.getBounds()) ||
            m_ball.getBounds().findIntersection(m_right.getBounds()))
        {
            m_ball.invertX();
            m_audio.playBounce();
        }

        if (m_ball.getPosition().y - 10.f <= 0.f ||
            m_ball.getPosition().y + 10.f >= windowSize.y)
        {
            m_ball.invertY();
            m_audio.playBounce();
        }

        if (m_ball.getPosition().x < 0.f)
        {
            m_rightScore++;
            m_audio.playScore();
            resetBall(windowSize, 1);
        }

        if (m_ball.getPosition().x > windowSize.x)
        {
            m_leftScore++;
            m_audio.playScore();
            resetBall(windowSize, -1);
        }
    }

    void GameCore::handleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            m_left.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            m_left.moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            m_right.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            m_right.moveDown();
    }

    void GameCore::resetBall(const sf::Vector2u &windowSize, int direction)
    {
        m_ball.reset(windowSize, direction);
    }
}
