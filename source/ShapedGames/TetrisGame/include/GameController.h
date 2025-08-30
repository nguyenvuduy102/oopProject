#pragma once
#include "GameCore.h"
#include "AudioManager.h"
#include "GameRenderer.h"
#include <SFML/Graphics.hpp>

namespace Tetris
{
    /**
     * @brief Manages user input and rendering for the Tetris game.
     */
    class GameController
    {
    public:
        /**
         * @brief Constructs a GameController with references to core, audio, and renderer.
         * @param core The GameCore for game logic.
         * @param audio The AudioManager for sounds.
         * @param renderer The GameRenderer for drawing.
         */
        GameController(GameCore &core, AudioManager &audio, GameRenderer &renderer);

        /**
         * @brief Handles user input for movement, rotation, pause, and game over menu.
         * @param window The SFML render window.
         */
        void HandleInput(sf::RenderWindow &window);

        /**
         * @brief Updates the game state (currently empty).
         */
        void Update();

        /**
         * @brief Renders the game using the renderer.
         * @param window The SFML render window.
         */
        void Render(sf::RenderWindow &window);

        /**
         * @brief Gets the user's choice in the game over menu.
         * @return 0 for YES, 1 for NO.
         */
        int GetGameOverChoice() const { return gameOverChoice; }

        /**
         * @brief Checks if the game is paused.
         * @return True if paused, false otherwise.
         */
        bool IsPaused() const { return paused; }

    private:
        GameCore &core;         ///< Reference to the game core.
        AudioManager &audio;    ///< Reference to the audio manager.
        GameRenderer &renderer; ///< Reference to the renderer.
        sf::Clock inputClock;   ///< Clock for input timing.
        float moveDelay = 0.15f; ///< Delay between movement inputs (seconds).
        int gameOverChoice = 0; ///< User's choice in game over menu (0=YES, 1=NO).
        bool paused = false;    ///< True if game is paused.
        bool prevP = false;     ///< Previous state of P key.
        bool prevLeft = false;  ///< Previous state of Left key.
        bool prevRight = false; ///< Previous state of Right key.
        bool prevEnter = false; ///< Previous state of Enter key.
    };
}