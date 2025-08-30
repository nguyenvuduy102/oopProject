/**
 * @file TextureManager.h
 * @brief Declares the TextureManager class, responsible for loading and managing textures for Flappy Bird.
 */

#pragma once // Prevent multiple includes
#include <SFML/Graphics.hpp>
#include <array>

namespace Flappy
{
    /**
     * @class TextureManager
     * @brief Responsible for loading and storing all textures used in Flappy Bird.
     *
     * Includes:
     * - Bird animation frames
     * - Pipe texture
     * - Background texture
     * - Game Over texture
     */
    class TextureManager
    {
    public:
        /**
         * @brief Default constructor. Initializes the TextureManager.
         */
        TextureManager();

        /**
         * @brief Load all required game textures.
         *
         * This function loads:
         * - 3 bird animation frames
         * - Pipe texture
         * - Background texture
         * - Game Over texture
         */
        void load();

        /**
         * @brief Get the bird texture for a given frame.
         * @param frame Frame index (0-2).
         * @return Texture for the given bird frame.
         */
        const sf::Texture &getBird(int frame) const { return m_bird[frame]; }

        /**
         * @brief Get the pipe texture.
         * @return Pipe texture.
         */
        const sf::Texture &getPipe() const { return m_pipe; }

        /**
         * @brief Get the background texture.
         * @return Background texture.
         */
        const sf::Texture &getBackground() const { return m_background; }

        /**
         * @brief Get the Game Over texture.
         * @return Game Over texture.
         */
        const sf::Texture &getGameover() const { return m_gameover; }

    private:
        std::array<sf::Texture, 3> m_bird; /**< Array of 3 bird animation frames */
        sf::Texture m_pipe;                /**< Pipe texture */
        sf::Texture m_background;          /**< Background texture */
        sf::Texture m_gameover;            /**< Game Over texture */
    };
}
