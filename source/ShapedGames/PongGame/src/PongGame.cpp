/**
 * @file PongGame.cpp
 * @brief Implementation of the PongGame class, the main entry point for running the Pong game.
 */

#include "../include/PongGame.h"

namespace Pong
{
    /**
     * @brief Construct a new PongGame object.
     *
     * Initializes the Pong game instance with default values.
     */
    PongGame::PongGame() {}

    /**
     * @brief Initialize the Pong game.
     *
     * Loads resources and prepares the game core and renderer.
     *
     * @param window Reference to the main SFML render window.
     */
    void PongGame::init(sf::RenderWindow &window)
    {
        m_core.init(window.getSize());
        m_renderer.load();
    }

    /**
     * @brief Run the main game loop.
     *
     * Handles window events, processes input, updates game logic,
     * and renders all game objects each frame until the window is closed
     * or Escape is pressed.
     *
     * @param window Reference to the main SFML render window.
     */
    void PongGame::run(sf::RenderWindow &window)
    {
        sf::Clock clock;
        while (window.isOpen())
        {
            while (auto eventOpt = window.pollEvent())
            {
                const sf::Event &event = *eventOpt;

                // Handle window close
                if (event.is<sf::Event::Closed>())
                {
                    window.close();
                    return;
                }

                // Handle Escape key press
                if (auto key = event.getIf<sf::Event::KeyPressed>())
                {
                    if (key->code == sf::Keyboard::Key::Escape)
                        return;
                }
            }

            // Process game input
            m_core.handleInput();

            // Update game state
            m_core.update(window.getSize());

            // Render game elements
            m_renderer.render(window,
                              m_core.leftPaddle(),
                              m_core.rightPaddle(),
                              m_core.ball(),
                              m_core.leftScore(),
                              m_core.rightScore());
        }
    }

    /**
     * @brief Clean up resources after the game ends.
     *
     * Currently does nothing, but can be expanded for resource management.
     */
    void PongGame::cleanup() {}
}
