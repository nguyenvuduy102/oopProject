#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "AudioManager.h"

namespace Pong
{
    /**
     * @class GameCore
     * @brief Core class that manages the main logic of the Pong game.
     *
     * This class handles initialization, updating game state, processing input,
     * tracking scores, and managing game objects such as paddles, ball, and audio.
     */
    class GameCore
    {
    public:
        /**
         * @brief Constructor for the GameCore class.
         */
        GameCore();

        /**
         * @brief Initialize the game state with the given window size.
         * @param windowSize The size of the render window.
         */
        void init(const sf::Vector2u &windowSize);

        /**
         * @brief Update the game logic, including ball and paddle movements, 
         * collision detection, and score handling.
         * @param windowSize The size of the render window.
         */
        void update(const sf::Vector2u &windowSize);

        /**
         * @brief Handle player input (e.g., paddle movement).
         */
        void handleInput();

        /**
         * @brief Get the left paddle (const version).
         * @return A const reference to the left Paddle.
         */
        const Paddle &leftPaddle() const { return m_left; }

        /**
         * @brief Get the left paddle (non-const version).
         * @return A reference to the left Paddle.
         */
        Paddle &leftPaddle() { return m_left; }

        /**
         * @brief Get the right paddle (const version).
         * @return A const reference to the right Paddle.
         */
        const Paddle &rightPaddle() const { return m_right; }

        /**
         * @brief Get the right paddle (non-const version).
         * @return A reference to the right Paddle.
         */
        Paddle &rightPaddle() { return m_right; }

        /**
         * @brief Get the ball (const version).
         * @return A const reference to the Ball.
         */
        const Ball &ball() const { return m_ball; }

        /**
         * @brief Get the ball (non-const version).
         * @return A reference to the Ball.
         */
        Ball &ball() { return m_ball; }

        /**
         * @brief Get the current score of the left player.
         * @return The left player's score.
         */
        int leftScore() const { return m_leftScore; }

        /**
         * @brief Get the current score of the right player.
         * @return The right player's score.
         */
        int rightScore() const { return m_rightScore; }

    private:
        Paddle m_left;        ///< Left paddle controlled by player or AI.
        Paddle m_right;       ///< Right paddle controlled by player or AI.
        Ball m_ball;          ///< Ball object used in the game.
        int m_leftScore;      ///< Score of the left player.
        int m_rightScore;     ///< Score of the right player.
        AudioManager m_audio; ///< Audio manager for playing game sounds.

        /**
         * @brief Reset the ball to the center of the window and set its direction.
         * @param windowSize The size of the render window.
         * @param direction The horizontal direction of the ball (-1 for left, 1 for right).
         */
        void resetBall(const sf::Vector2u &windowSize, int direction);
    };
}
