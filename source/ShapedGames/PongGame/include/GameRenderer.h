#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

namespace Pong
{
    class GameRenderer
    {
    public:
        GameRenderer();
        void load();
        void render(sf::RenderWindow &window,
                    const Paddle &left,
                    const Paddle &right,
                    const Ball &ball,
                    int leftScore,
                    int rightScore);

    private:
        sf::Font m_font;
        sf::Text m_scoreText;
    };
}
