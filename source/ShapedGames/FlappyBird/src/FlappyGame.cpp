#include "../include/FlappyGame.h"

namespace Flappy
{
    FlappyGame::FlappyGame() : m_core(nullptr), m_renderer(nullptr) {}

    void FlappyGame::init(sf::RenderWindow &window)
    {
        m_textures.load();
        m_core = new GameCore(m_textures);
        m_core->init(window.getSize());
        m_renderer = new GameRenderer(m_textures);
        m_renderer->load();
    }

    void FlappyGame::run(sf::RenderWindow &window)
    {
        sf::Clock clock;
        int frames = 0;
        GameState state = GameState::Waiting;

        while (window.isOpen())
        {
            GameState newState = state;

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
                    if (key->code == sf::Keyboard::Key::C && state == GameState::Gameover)
                    {
                        newState = GameState::Waiting;
                        m_core->reset(window.getSize());
                    }
                }
            }

            m_core->handleInput(state, newState);

            float delta = clock.restart().asSeconds();

            if (state == GameState::Started)
                m_core->update(window.getSize(), delta, frames);

            m_renderer->render(window, m_core->bird(), m_core->pipes(), m_core->score(), state, frames);

            state = newState;
            frames++;
        }
    }

    void FlappyGame::cleanup()
    {
        delete m_core;
        delete m_renderer;
    }
}
