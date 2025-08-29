#include "../include/PongGame.h"

namespace Pong
{
    PongGame::PongGame() {}

    void PongGame::init(sf::RenderWindow &window)
    {
        m_core.init(window.getSize());
        m_renderer.load();
    }

    void PongGame::run(sf::RenderWindow &window)
    {
        sf::Clock clock;
        while (window.isOpen())
        {
            while (auto eventOpt = window.pollEvent())
            {
                const sf::Event &event = *eventOpt;
                if (event.is<sf::Event::Closed>())
                {
                    window.close();
                    return;
                }
                if (auto key = event.getIf<sf::Event::KeyPressed>())
                {
                    if (key->code == sf::Keyboard::Key::Escape)
                        return;
                }
            }

            m_core.handleInput();
            m_core.update(window.getSize());
            m_renderer.render(window,
                              m_core.leftPaddle(),
                              m_core.rightPaddle(),
                              m_core.ball(),
                              m_core.leftScore(),
                              m_core.rightScore());
        }
    }

    void PongGame::cleanup() {}
}
