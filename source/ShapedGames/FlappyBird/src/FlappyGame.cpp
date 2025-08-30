#include "../include/FlappyGame.h"

namespace Flappy
{
    // Constructor, init pointers to null
    FlappyGame::FlappyGame() : m_core(nullptr), m_renderer(nullptr) {}

    // Setup game stuff
    void FlappyGame::init(sf::RenderWindow &window)
    {
        m_textures.load();                         // Load textures
        m_core = new GameCore(m_textures);         // Make game core
        m_core->init(window.getSize());            // Init core with window size
        m_renderer = new GameRenderer(m_textures); // Make renderer
        m_renderer->load();                        // Load renderer stuff
    }

    // Run game loop
    void FlappyGame::run(sf::RenderWindow &window)
    {
        sf::Clock clock;                      // For timing
        int frames = 0;                       // Track frames
        GameState state = GameState::Waiting; // Start in waiting state

        // Main loop
        while (window.isOpen())
        {
            GameState newState = state; // Track state changes

            // Handle events
            while (auto eventOpt = window.pollEvent())
            {
                const sf::Event &event = *eventOpt;
                if (event.is<sf::Event::Closed>()) // If window closed
                {
                    window.close(); // Shut it down
                    return;
                }
                if (auto key = event.getIf<sf::Event::KeyPressed>()) // If key pressed
                {
                    if (key->code == sf::Keyboard::Key::Escape) // ESC to exit
                        return;
                    if (key->code == sf::Keyboard::Key::C && state == GameState::Gameover) // C to restart
                    {
                        newState = GameState::Waiting;   // Back to waiting
                        m_core->reset(window.getSize()); // Reset game
                    }
                }
            }

            // Handle input and update state
            m_core->handleInput(state, newState);

            // Get time since last frame
            float delta = clock.restart().asSeconds();

            // Update game if started
            if (state == GameState::Started)
                m_core->update(window.getSize(), delta, frames);

            // Draw everything
            m_renderer->render(window, m_core->bird(), m_core->pipes(), m_core->score(), state, frames);

            state = newState; // Update state
            frames++;         // Count frames
        }
    }

    // Clean up game stuff
    void FlappyGame::cleanup()
    {
        delete m_core;     // Free core
        delete m_renderer; // Free renderer
    }
}