/**
 * @file TextureManager.h
 * @brief Khai báo lớp TextureManager, chịu trách nhiệm tải và quản lý texture cho Flappy Bird.
 */

#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include <array>

namespace Flappy
{
    /**
     * @class TextureManager
     * @brief Lớp chịu trách nhiệm tải và lưu trữ tất cả các texture được sử dụng trong game Flappy Bird.
     *
     * Bao gồm:
     * - Các frame animation của chim.
     * - Texture ống (Pipe).
     * - Texture background.
     * - Texture Game Over.
     */
    class TextureManager
    {
    public:
        /**
         * @brief Constructor mặc định. Khởi tạo TextureManager.
         */
        TextureManager();

        /**
         * @brief Tải tất cả texture cần thiết cho game.
         *
         * Hàm này sẽ load toàn bộ:
         * - 3 frame animation của chim.
         * - Texture ống.
         * - Texture background.
         * - Texture màn hình game over.
         */
        void load();

        /**
         * @brief Lấy texture của chim theo frame.
         * @param frame Chỉ số frame (0-2).
         * @return Texture tương ứng với frame của chim.
         */
        const sf::Texture &getBird(int frame) const { return m_bird[frame]; }

        /**
         * @brief Lấy texture của ống.
         * @return Texture của ống.
         */
        const sf::Texture &getPipe() const { return m_pipe; }

        /**
         * @brief Lấy texture của background.
         * @return Texture của background.
         */
        const sf::Texture &getBackground() const { return m_background; }

        /**
         * @brief Lấy texture của màn hình Game Over.
         * @return Texture của Game Over.
         */
        const sf::Texture &getGameover() const { return m_gameover; }

    private:
        std::array<sf::Texture, 3> m_bird; /**< Mảng 3 frame animation của chim */
        sf::Texture m_pipe;                /**< Texture ống */
        sf::Texture m_background;          /**< Texture background */
        sf::Texture m_gameover;            /**< Texture màn hình Game Over */
    };
}
