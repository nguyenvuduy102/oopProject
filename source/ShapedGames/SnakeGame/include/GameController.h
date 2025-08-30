#pragma once
#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include "Snake.h"
#include "Food.h"
#include <optional>

namespace Snake
{
    /**
     * @brief Enumerates the possible game modes.
     */
    enum class Mode
    {
        Menu,       ///< The main menu state.
        OnePlayer,  ///< Single-player game mode.
        TwoPlayers, ///< Two-player game mode.
        GameOver    ///< Game over state.
    };

    /**
     * @brief Manages the game logic, including snake movement, collisions, and game modes.
     */
    class GameController
    {
    public:
        /**
         * @brief Constructs a GameController, initializing the game state.
         * @param audio Reference to the AudioManager for sound effects and music.
         */
        GameController(AudioManager &audio);

        /**
         * @brief Initializes the game state, resetting scores, snakes, and food.
         */
        void init();

        /**
         * @brief Updates the game state, moving snakes and checking collisions.
         */
        void update();

        /**
         * @brief Handles input events based on the current game mode.
         * @param ev The SFML event to process (optional).
         */
        void handleEvent(const std::optional<sf::Event> &ev);

        /**
         * @brief Gets the current game mode.
         * @return The current Mode (Menu, OnePlayer, TwoPlayers, or GameOver).
         */
        Mode mode() const { return m_mode; }

        /**
         * @brief Gets the first player's snake (non-const).
         * @return Reference to the first player's snake.
         */
        Snake &player1() { return m_p1; }

        /**
         * @brief Gets the first player's snake (const).
         * @return Const reference to the first player's snake.
         */
        const Snake &player1() const { return m_p1; }

        /**
         * @brief Gets the second player's snake (non-const).
         * @return Reference to the second player's snake.
         */
        Snake &player2() { return m_p2; }

        /**
         * @brief Gets the second player's snake (const).
         * @return Const reference to the second player's snake.
         */
        const Snake &player2() const { return m_p2; }

        /**
         * @brief Gets the food object (non-const).
         * @return Reference to the food object.
         */
        Food &food() { return m_food; }

        /**
         * @brief Gets the food object (const).
         * @return Const reference to the food object.
         */
        const Food &food() const { return m_food; }

        /**
         * @brief Gets the score of the first player.
         * @return The first player's score.
         */
        int score1() const { return m_score1; }

        /**
         * @brief Gets the score of the second player.
         * @return The second player's score.
         */
        int score2() const { return m_score2; }

        /**
         * @brief Creates a grid of lines for rendering the game board.
         * @param size The size of each grid cell in pixels.
         * @param c The color of the grid lines.
         * @return A vertex array representing the grid lines.
         */
        sf::VertexArray DrawGrid(int size, sf::Color c) const;

    private:
        /**
         * @brief Starts a single-player game, initializing the snake and game state.
         */
        void startOnePlayer();

        /**
         * @brief Starts a two-player game, initializing both snakes and game state.
         */
        void startTwoPlayers();

        AudioManager &m_audio;          ///< Reference to the audio manager for sounds.
        Mode m_mode = Mode::Menu;       ///< Current game mode.
        Snake m_p1, m_p2;               ///< The two snakes (player 1 and player 2).
        Food m_food;                    ///< The food object in the game.
        int m_score1 = 0, m_score2 = 0; ///< Scores for player 1 and player 2.
        sf::Clock m_clock;              ///< Clock for timing game updates.
        float m_moveInterval = 0.14f;   ///< Interval between snake movements (seconds).
    };
}