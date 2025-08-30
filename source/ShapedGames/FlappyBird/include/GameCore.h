#pragma once // Prevent multiple includes
#include <SFML/Graphics.hpp>
#include <deque>
#include <random>
#include "Bird.h"
#include "Pipe.h"
#include "AudioManager.h"
#include "TextureManager.h"

/**
 * @file GameCore.h
 * @brief Declares the GameCore class, which handles the main logic of Flappy Bird.
 */

namespace Flappy
{
    /**
     * @enum GameState
     * @brief Represents the current state of the game.
     */
    enum class GameState
    {
        Waiting, /**< Before the game starts */
        Started, /**< The game is running */
        Gameover /**< The game has ended */
    };

    /**
     * @class GameCore
     * @brief Handles the entire game logic of Flappy Bird.
     *
     * Responsibilities:
     * - Manage the bird (Bird), pipes (Pipe), and audio (AudioManager).
     * - Handle input, collision detection, and scoring.
     * - Randomly generate pipes and update the game state.
     */
    class GameCore
    {
    public:
        /**
         * @brief Constructor.
         * @param tex Reference to the TextureManager for managing textures.
         */
        GameCore(TextureManager &tex);

        /**
         * @brief Initialize the game with the window size.
         * @param windowSize Size of the rendering window.
         */
        void init(const sf::Vector2u &windowSize);

        /**
         * @brief Update the game state.
         * @param windowSize Size of the rendering window.
         * @param delta Time elapsed between frames (seconds).
         * @param frames Frame count used to control animation.
         */
        void update(const sf::Vector2u &windowSize, float delta, int frames);

        /**
         * @brief Handle player input and update game state if needed.
         * @param state Current state of the game.
         * @param newState New state of the game after processing input.
         */
        void handleInput(GameState state, GameState &newState);

        /**
         * @brief Get the bird (modifiable).
         * @return Reference to Bird.
         */
        Bird &bird() { return m_bird; }

        /**
         * @brief Get the bird (read-only).
         * @return Const reference to Bird.
         */
        const Bird &bird() const { return m_bird; }

        /**
         * @brief Get the list of pipes.
         * @return Const reference to a deque of Pipe objects.
         */
        const std::deque<Pipe> &pipes() const { return m_pipes; }

        /**
         * @brief Get the current score.
         * @return Player's score.
         */
        int score() const { return m_score; }

        /**
         * @brief Reset the game to its initial state.
         * @param windowSize Size of the rendering window.
         */
        void reset(const sf::Vector2u &windowSize);

    private:
        TextureManager &m_textures; /**< Texture manager */
        Bird m_bird;                /**< Bird instance */
        std::deque<Pipe> m_pipes;   /**< List of pipes */
        AudioManager m_audio;       /**< Audio manager */
        std::mt19937 m_rng;         /**< Random number generator */
        int m_score;                /**< Current score */
        float m_gravity;            /**< Gravity applied to the bird */
        float m_flapImpulse;        /**< Impulse strength when flapping */
        float m_pipeInterval;       /**< Time interval between pipe spawns */
        float m_pipeGap;            /**< Vertical gap between top and bottom pipes */
        float m_pipeSpeed;          /**< Speed of pipe movement */
        float m_spawnTimer;         /**< Timer for spawning pipes */

        /**
         * @brief Spawn a new pipe.
         * @param windowSize Size of the rendering window.
         */
        void spawnPipe(const sf::Vector2u &windowSize);

        /**
         * @brief Check for collisions between the bird and pipes or the ground.
         * @param windowSize Size of the rendering window.
         * @return true if a collision occurred, false otherwise.
         */
        bool checkCollision(const sf::Vector2u &windowSize);
    };
}
