#pragma once // Prevent multiple includes
#include "../../../GameMain/Core/include/IGame.h"
#include "GameCore.h"
#include "GameRenderer.h"
#include "TextureManager.h"

/**
 * @file FlappyGame.h
 * @brief Declares the FlappyGame class, the main controller of the Flappy Bird game.
 */

namespace Flappy
{
    /**
     * @class FlappyGame
     * @brief Main class of the Flappy Bird game.
     *
     * This class inherits from IGame and manages the entire game lifecycle:
     * - Initialization of game systems
     * - Running the main game loop
     * - Cleaning up resources on exit
     * - Providing the game name
     */
    class FlappyGame : public IGame
    {
    public:
        /**
         * @brief Constructor. Sets up the game components.
         */
        FlappyGame();

        /**
         * @brief Initialize the game with the rendering window.
         * @param window Reference to the sf::RenderWindow used to draw the game.
         */
        void init(sf::RenderWindow &window) override;

        /**
         * @brief Run the main game loop.
         * @param window Reference to the sf::RenderWindow used to render frames.
         */
        void run(sf::RenderWindow &window) override;

        /**
         * @brief Release all resources when the game ends.
         */
        void cleanup() override;

        /**
         * @brief Get the name of the game.
         * @return String containing the game name ("Flappy Bird").
         */
        std::string name() const override { return "Flappy Bird"; }

    private:
        TextureManager m_textures; /**< Manages textures for the game */
        GameCore *m_core;          /**< Handles core game logic */
        GameRenderer *m_renderer;  /**< Handles rendering of the game */
    };
}
