#pragma once
#include "../../../GameMain/Core/include/IGame.h"
#include "GameCore.h"
#include "GameRenderer.h"

namespace Pong
{
    /**
     * @class PongGame
     * @brief Main game class for Pong, implementing the IGame interface.
     *
     * This class is responsible for initializing, running, and cleaning up
     * the Pong game. It serves as the entry point for integrating Pong
     * into the overall game framework.
     */
    class PongGame : public IGame
    {
    public:
        /**
         * @brief Construct a new PongGame object.
         */
        PongGame();

        /**
         * @brief Initialize the Pong game with the given window.
         *
         * Loads resources and prepares game components for execution.
         *
         * @param window Reference to the SFML render window.
         */
        void init(sf::RenderWindow &window) override;

        /**
         * @brief Run the main game loop for Pong.
         *
         * Handles input, updates game logic, and renders game objects
         * until the game is terminated.
         *
         * @param window Reference to the SFML render window.
         */
        void run(sf::RenderWindow &window) override;

        /**
         * @brief Clean up resources used by the Pong game.
         */
        void cleanup() override;

        /**
         * @brief Get the name of the game.
         *
         * @return std::string The name "Pong".
         */
        std::string name() const override { return "Pong"; }

    private:
        GameCore m_core;       ///< Core game logic handler.
        GameRenderer m_renderer; ///< Responsible for rendering game objects.
    };
}
