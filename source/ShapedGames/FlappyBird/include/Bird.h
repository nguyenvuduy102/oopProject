#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

/**
 * @file Bird.h
 * @brief Khai báo lớp Bird, xử lý di chuyển và hoạt ảnh chim trong game Flappy Bird.
 */

namespace Flappy
{
    /**
     * @class Bird
     * @brief Lớp điều khiển chim (chuyển động và hoạt ảnh).
     *
     * Lớp này chịu trách nhiệm:
     * - Quản lý sprite của chim
     * - Cập nhật vị trí với trọng lực và va chạm
     * - Xử lý hoạt ảnh vỗ cánh
     */
    class Bird
    {
    public:
        /**
         * @brief Constructor, khởi tạo chim với texture.
         * @param tex Tham chiếu tới TextureManager để lấy texture của chim.
         */
        Bird(const TextureManager &tex);

        /**
         * @brief Reset lại vị trí và trạng thái của chim.
         * @param windowSize Kích thước cửa sổ trò chơi.
         */
        void reset(const sf::Vector2u &windowSize);

        /**
         * @brief Làm chim nhảy với một xung lực.
         * @param impulse Giá trị vận tốc được cộng thêm khi nhảy.
         */
        void flap(float impulse);

        /**
         * @brief Cập nhật trạng thái chim (chuyển động và hoạt ảnh).
         * @param gravity Giá trị trọng lực.
         * @param frames Số khung hình cho hoạt ảnh.
         * @param animate Bật/tắt hoạt ảnh.
         * @param physics Bật/tắt vật lý.
         */
        void update(float gravity, int frames, bool animate, bool physics);

        /**
         * @brief Lấy sprite của chim để vẽ (có thể chỉnh sửa).
         * @return Tham chiếu tới sprite của chim.
         */
        sf::Sprite &sprite() { return m_sprite; }

        /**
         * @brief Lấy sprite của chim để đọc (const).
         * @return Tham chiếu const tới sprite của chim.
         */
        const sf::Sprite &sprite() const { return m_sprite; }

        /**
         * @brief Lấy hitbox (vùng va chạm) của chim.
         * @return Hình chữ nhật FloatRect bao quanh chim.
         */
        sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }

        /**
         * @brief Lấy vị trí hiện tại của chim.
         * @return Vector2f vị trí chim trong cửa sổ.
         */
        sf::Vector2f getPosition() const { return m_sprite.getPosition(); }

    private:
        const TextureManager &m_textures; /**< Tham chiếu tới TextureManager */
        sf::Sprite m_sprite;              /**< Sprite của chim */
        float m_velocity;                 /**< Vận tốc theo trục Y của chim */
        int m_frame;                      /**< Frame hoạt ảnh hiện tại */
    };
}
