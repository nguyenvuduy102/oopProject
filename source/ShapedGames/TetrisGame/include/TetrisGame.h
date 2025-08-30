#pragma once
#include "../../../GameMain/Core/include/BaseGame.h"
#include "GameCore.h"
#include "GameRenderer.h"
#include "GameController.h"
#include "AudioManager.h"
#include <SFML/Graphics.hpp>

namespace Tetris
{
    /**
     * @brief The main game class for Tetris, implementing the IGame interface.
     */
    class TetrisGame : public IGame
    {
    public:
        /**
         * @brief Constructs a TetrisGame instance, initializing core components.
         */
        TetrisGame();

        /**
         * @brief Initializes the game, loading font and setting up renderer and controller.
         * @param window The SFML render window.
         * @throws std::runtime_error If the font fails to load.
         */
        void init(sf::RenderWindow &window) override;

        /**
         * @brief Runs the main game loop, including countdown, input handling, and rendering.
         * @param window The SFML render window.
         */
        void run(sf::RenderWindow &window) override;

        /**
         * @brief Cleans up game resources, deleting renderer and controller.
         */
        void cleanup() override;

        /**
         * @brief Gets the name of the game.
         * @return The string "Tetris".
         */
        std::string name() const override { return "Tetris"; }

    private:
        GameCore core;           ///< Manages game logic and state.
        AudioManager audio;      ///< Manages audio resources.
        sf::Font font;           ///< Font for text rendering.
        GameRenderer *renderer;   ///< Pointer to the game renderer.
        GameController *controller; ///< Pointer to the game controller.
    };
}