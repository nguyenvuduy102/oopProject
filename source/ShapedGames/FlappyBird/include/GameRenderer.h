/**
 * @file GameRenderer.h
 * @brief Khai báo lớp GameRenderer, chịu trách nhiệm vẽ toàn bộ nội dung game Flappy Bird.
 */

#pragma once // Stop multiple includes
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
     * @brief Lớp chịu trách nhiệm vẽ các đối tượng và giao diện của trò chơi Flappy Bird.
     *
     * Chức năng chính:
     * - Vẽ chim (Bird), ống (Pipe), điểm số và giao diện kết thúc game.
     * - Quản lý font chữ, background và texture.
     */
    class GameRenderer
    {
    public:
        /**
         * @brief Constructor.
         * @param tex Tham chiếu tới TextureManager để quản lý texture.
         */
        GameRenderer(TextureManager &tex);

        /**
         * @brief Tải font và texture cần thiết cho việc render.
         */
        void load();

        /**
         * @brief Vẽ toàn bộ khung hình của trò chơi lên cửa sổ.
         * @param window Cửa sổ render.
         * @param bird Chim trong game.
         * @param pipes Danh sách các ống.
         * @param score Điểm số hiện tại.
         * @param state Trạng thái game (đang chờ, đang chạy, game over).
         * @param frames Số frame để điều khiển hoạt ảnh.
         */
        void render(sf::RenderWindow &window,
                    const Bird &bird,
                    const std::deque<Pipe> &pipes,
                    int score,
                    GameState state,
                    int frames);

    private:
        TextureManager &m_textures;             /**< Tham chiếu tới TextureManager */
        sf::Font m_font;                        /**< Font chữ để hiển thị điểm */
        sf::Text m_scoreText;                   /**< Text hiển thị điểm số */
        std::array<sf::Sprite, 6> m_background; /**< Mảng sprite background */
        sf::Sprite m_gameover;                  /**< Hình ảnh "Game Over" */
        sf::Text m_pressC;                      /**< Text hướng dẫn "Press C" */
    };
}
