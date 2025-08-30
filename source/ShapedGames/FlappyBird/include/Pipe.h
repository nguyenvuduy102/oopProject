/**
 * @file Pipe.h
 * @brief Declares the Pipe class, which manages a pair of pipes (upper and lower) in the Flappy Bird game.
 */

#pragma once // Prevent multiple includes
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace Flappy
{
    /**
     * @class Pipe
     * @brief Manages a pair of pipes (upper and lower).
     *
     * Responsibilities:
     * - Initialize pipe positions and the gap between them.
     * - Update pipe position based on movement speed.
     * - Check for collisions, off-screen status, and scoring.
     */
    class Pipe
    {
    public:
        /**
         * @brief Constructor.
         * @param x X position of the pipe.
         * @param gapY Y position of the gap between the two pipes.
         * @param gapHeight Height of the gap.
         * @param tex Texture manager (TextureManager).
         * @param windowHeight Height of the game window.
         */
        Pipe(float x, float gapY, float gapHeight, const TextureManager &tex, float windowHeight);

        /**
         * @brief Update the pipe’s position based on speed.
         * @param speed Movement speed (along the X axis).
         */
        void update(float speed);

        /**
         * @brief Get the upper pipe sprite.
         * @return Const reference to the upper pipe sprite.
         */
        const sf::Sprite &upper() const { return m_upper; }

        /**
         * @brief Get the lower pipe sprite.
         * @return Const reference to the lower pipe sprite.
         */
        const sf::Sprite &lower() const { return m_lower; }

        /**
         * @brief Check if the pipe has moved off-screen.
         * @return true if the pipe is off-screen, false otherwise.
         */
        bool isOffScreen() const;

        /**
         * @brief Check if this pipe has already been scored.
         * @return true if already scored, false otherwise.
         */
        bool hasScored() const { return m_scored; }

        /**
         * @brief Mark this pipe as scored.
         */
        void setScored() { m_scored = true; }

    private:
        sf::Sprite m_upper; /**< Sprite for the upper pipe */
        sf::Sprite m_lower; /**< Sprite for the lower pipe */
        bool m_scored;      /**< Whether this pipe has been scored already */
    };
}
