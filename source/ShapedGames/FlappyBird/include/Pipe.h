/**
 * @file Pipe.h
 * @brief Khai báo lớp Pipe, quản lý một cặp ống (trên và dưới) trong trò chơi Flappy Bird.
 */

#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace Flappy
{
    /**
     * @class Pipe
     * @brief Lớp quản lý một cặp ống (trên và dưới).
     *
     * Chức năng chính:
     * - Khởi tạo vị trí và kích thước khoảng cách giữa các ống.
     * - Cập nhật vị trí ống theo tốc độ di chuyển.
     * - Kiểm tra va chạm, ngoài màn hình, và điểm số.
     */
    class Pipe
    {
    public:
        /**
         * @brief Constructor.
         * @param x Vị trí X của ống.
         * @param gapY Vị trí Y của khoảng trống giữa 2 ống.
         * @param gapHeight Chiều cao khoảng trống.
         * @param tex Quản lý texture (TextureManager).
         * @param windowHeight Chiều cao của cửa sổ game.
         */
        Pipe(float x, float gapY, float gapHeight, const TextureManager &tex, float windowHeight);

        /**
         * @brief Cập nhật vị trí ống dựa trên tốc độ.
         * @param speed Tốc độ di chuyển (theo trục X).
         */
        void update(float speed);

        /**
         * @brief Lấy sprite của ống trên.
         * @return Tham chiếu hằng đến sprite của ống trên.
         */
        const sf::Sprite &upper() const { return m_upper; }

        /**
         * @brief Lấy sprite của ống dưới.
         * @return Tham chiếu hằng đến sprite của ống dưới.
         */
        const sf::Sprite &lower() const { return m_lower; }

        /**
         * @brief Kiểm tra xem ống đã đi ra ngoài màn hình chưa.
         * @return true nếu ống ra khỏi màn hình, false nếu chưa.
         */
        bool isOffScreen() const;

        /**
         * @brief Kiểm tra xem ống đã được tính điểm chưa.
         * @return true nếu đã tính điểm, false nếu chưa.
         */
        bool hasScored() const { return m_scored; }

        /**
         * @brief Đánh dấu ống đã được tính điểm.
         */
        void setScored() { m_scored = true; }

    private:
        sf::Sprite m_upper; /**< Sprite cho ống trên */
        sf::Sprite m_lower; /**< Sprite cho ống dưới */
        bool m_scored;      /**< Đã được tính điểm hay chưa */
    };
}
