#include "../include/SnakeGame.h"
#include <iostream>

namespace Snake
{
    SnakeGame::SnakeGame()
        : m_controller(m_audio)
    {
    }
    void SnakeGame::init(sf::RenderWindow &window)
    {
        if (m_initialized)
            return;

        m_renderer = new GameRenderer(window);
        m_audio.PlayMusic();
        m_initialized = true;
    }

    void SnakeGame::run(sf::RenderWindow &window)
    {
        init(window);
        while (window.isOpen())
        {
            while (auto ev = window.pollEvent())
            {
                if (ev->is<sf::Event::Closed>())
                    window.close();

                m_controller.handleEvent(ev);

                if (m_controller.mode() == Mode::GameOver)
                {
                    if (auto key = ev->getIf<sf::Event::KeyPressed>())
                        if (key->code == sf::Keyboard::Key::Escape)
                            return;
                }
            }

            m_controller.update();
            m_renderer->render(m_controller);
        }
    }

    void SnakeGame::cleanup()
    {
        m_audio.StopMusic();
        if (m_renderer)
        {
            delete m_renderer;
            m_renderer = nullptr;
        }
        m_initialized = false;
    }
}
