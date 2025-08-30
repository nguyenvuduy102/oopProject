#pragma once
#include <SFML/Graphics.hpp>
#include "GameCore.h"

namespace Tetris
{
    /**
     * @brief Handles rendering of the Tetris game, including grid, blocks, and UI.
     */
    class GameRenderer
    {
    public:
        /**
         * @brief Constructs a GameRenderer with a font and optional background image.
         * @param font The SFML font for text rendering.
         * @param bgPath Path to the background image (optional).
         */
        GameRenderer(sf::Font &font, const std::string &bgPath);

        /**
         * @brief Draws the entire game scene, including grid, blocks, and UI.
         * @param window The SFML render window.
         * @param core The GameCore providing game state.
         * @param choice The user's choice in the game over menu (0 for YES, 1 for NO).
         * @param paused True if the game is paused.
         */
        void Draw(sf::RenderWindow &window, GameCore &core, int choice, bool paused);

        /**
         * @brief Draws the next block preview.
         * @param window The SFML render window.
         * @param next The next Block to draw.
         */
        void DrawNext(sf::RenderWindow &window, const Block &next);

    private:
        /**
         * @brief Draws the user interface elements like score, lines, level, pause overlay, and game over menu.
         * @param window The SFML render window.
         * @param core The GameCore providing game data.
         * @param choice The user's choice in the game over menu.
         * @param paused True if the game is paused.
         */
        void DrawUI(sf::RenderWindow &window, GameCore &core, int choice, bool paused);

        sf::Font &font;                       ///< Font for text rendering.
        sf::Texture bgTexture;                ///< Texture for the background image.
        std::unique_ptr<sf::Sprite> bgSprite; ///< Sprite for the background image.
        bool hasBackground = false;           ///< True if a background image is loaded.
    };
}