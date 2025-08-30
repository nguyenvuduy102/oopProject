#pragma once
#include "../../../GameMain/Core/include/IGame.h"
#include "GameRenderer.h"
#include "GameController.h"
#include "AudioManager.h"

namespace Snake
{
    /**
     * @brief The main game class for the Snake game, implementing the IGame interface.
     */
    class SnakeGame : public IGame
    {
    public:
        /**
         * @brief Constructs a SnakeGame instance, initializing the game controller and audio manager.
         */
        SnakeGame();

        /**
         * @brief Initializes the game, setting up the renderer and starting background music.
         * @param window The SFML render window for the game.
         */
        void init(sf::RenderWindow &window) override;

        /**
         * @brief Runs the main game loop, handling events, updates, and rendering.
         * @param window The SFML render window for the game.
         */
        void run(sf::RenderWindow &window) override;

        /**
         * @brief Cleans up game resources, stopping music and deleting the renderer.
         */
        void cleanup() override;

        /**
         * @brief Gets the name of the game.
         * @return The string "Snake".
         */
        std::string name() const override { return "Snake"; }

    private:
        GameRenderer *m_renderer{nullptr}; ///< Pointer to the game renderer.
        AudioManager m_audio;              ///< Manages audio resources.
        GameController m_controller;       ///< Manages game logic and state.
        bool m_initialized{false};         ///< Tracks whether the game is initialized.
    };
}