#include "../include/FlappyGame.h"

namespace Flappy
{
    /**
     * @brief Default constructor. Initializes pointers to nullptr.
     */
    FlappyGame::FlappyGame() : m_core(nullptr), m_renderer(nullptr) {}

    /**
     * @brief Initialize the game by loading textures, creating the core, and setting up the renderer.
     * @param window Reference to the SFML render window.
     */
    void FlappyGame::init(sf::RenderWindow &window)
    {
        m_textures.load();                          // Load all game textures
        m_core = new GameCore(m_textures);          // Create game core
        m_core->init(window.getSize());             // Initialize core with window size
        m_renderer = new GameRenderer(m_textures);  // Create renderer
        m_renderer->load();                         // Load renderer assets
    }

    /**
     * @brief Main game loop. Handles input, updates game state, and renders frames.
     * @param window Reference to the SFML render window.
     */
    void FlappyGame::run(sf::RenderWindow &window)
    {
        sf::Clock clock;                       // Clock to measure delta time
        int frames = 0;                        // Frame counter
        GameState state = GameState::Waiting;  // Start in "waiting" state

        // Main loop
        while (window.isOpen())
        {
            GameState newState = state;  // Temporary state tracker

            // --- Handle events ---
            while (auto eventOpt = window.pollEvent())
            {
                const sf::Event &event = *eventOpt;

                // Handle window close event
                if (event.is<sf::Event::Closed>())
                {
                    window.close();
                    return;
                }

                // Handle key presses
                if (auto key = event.getIf<sf::Event::KeyPressed>())
                {
                    if (key->code == sf::Keyboard::Key::Escape)  // Exit game
                        return;

                    if (key->code == sf::Keyboard::Key::C && state == GameState::Gameover)  // Restart after game over
                    {
                        newState = GameState::Waiting;
                        m_core->reset(window.getSize());  // Reset game state
                    }
                }
            }

            // --- Game logic ---
            m_core->handleInput(state, newState);  // Process input and possibly update state

            float delta = clock.restart().asSeconds();  // Time since last frame

            if (state == GameState::Started)  // Only update logic if game is running
                m_core->update(window.getSize(), delta, frames);

            // --- Rendering ---
            m_renderer->render(window,
                               m_core->bird(),
                               m_core->pipes(),
                               m_core->score(),
                               state,
                               frames);

            // Apply updated state and frame counter
            state = newState;
            frames++;
        }
    }

    /**
     * @brief Clean up allocated resources.
     */
    void FlappyGame::cleanup()
    {
        delete m_core;
        delete m_renderer;
    }
}
