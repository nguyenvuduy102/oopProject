/**
 * @file GameRenderer.h
 * @brief Declares the GameRenderer class, responsible for rendering the entire Flappy Bird game.
 */

#pragma once // Prevent multiple includes
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Pipe.h"
#include "TextureManager.h"
#include "GameCore.h"
#include <array>

namespace Flappy
{
    /**
     * @class GameRenderer
     * @brief Responsible for rendering all game objects and UI in Flappy Bird.
     *
     * Main responsibilities:
     * - Draw the bird (Bird), pipes (Pipe), score, and game-over screen.
     * - Manage fonts, background, and textures.
     */
    class GameRenderer
    {
    public:
        /**
         * @brief Constructor.
         * @param tex Reference to TextureManager for texture management.
         */
        GameRenderer(TextureManager &tex);

        /**
         * @brief Load fonts and textures required for rendering.
         */
        void load();

        /**
         * @brief Render the entire game frame onto the window.
         * @param window The render window.
         * @param bird The bird in the game.
         * @param pipes List of pipes.
         * @param score Current score.
         * @param state Game state (waiting, running, or game over).
         * @param frames Frame counter for animation.
         */
        void render(sf::RenderWindow &window,
                    const Bird &bird,
                    const std::deque<Pipe> &pipes,
                    int score,
                    GameState state,
                    int frames);

    private:
        TextureManager &m_textures;             /**< Reference to TextureManager */
        sf::Font m_font;                        /**< Font for displaying score */
        sf::Text m_scoreText;                   /**< Text displaying the score */
        std::array<sf::Sprite, 6> m_background; /**< Array of background sprites */
        sf::Sprite m_gameover;                  /**< "Game Over" image */
        sf::Text m_pressC;                      /**< Instruction text: "Press C" */
    };
}
