#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "AudioManager.h"

namespace Pong
{
    class GameCore
    {
    public:
        GameCore();
        void init(const sf::Vector2u &windowSize);
        void update(const sf::Vector2u &windowSize);
        void handleInput();
        const Paddle &leftPaddle() const { return m_left; }
        Paddle &leftPaddle() { return m_left; }
        const Paddle &rightPaddle() const { return m_right; }
        Paddle &rightPaddle() { return m_right; }
        const Ball &ball() const { return m_ball; }
        Ball &ball() { return m_ball; }
        int leftScore() const { return m_leftScore; }
        int rightScore() const { return m_rightScore; }

    private:
        Paddle m_left;
        Paddle m_right;
        Ball m_ball;
        int m_leftScore;
        int m_rightScore;
        AudioManager m_audio;
        void resetBall(const sf::Vector2u &windowSize, int direction);
    };
}
