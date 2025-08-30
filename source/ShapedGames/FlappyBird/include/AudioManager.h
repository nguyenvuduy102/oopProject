#pragma once // Stop multiple includes
#include <SFML/Audio.hpp>

namespace Flappy
{
    /**
     * @class AudioManager
     * @brief Quản lý âm thanh cho game Flappy Bird.
     *
     * Lớp này chịu trách nhiệm tải và phát các hiệu ứng âm thanh:
     * - Tiếng vỗ cánh khi chim nhảy
     * - Tiếng ghi điểm khi chim vượt qua ống
     * - Tiếng va chạm khi chim đâm vào chướng ngại vật
     */
    class AudioManager
    {
    public:
        /**
         * @brief Constructor.
         *
         * Khởi tạo AudioManager và thiết lập âm thanh.
         */
        AudioManager();

        /**
         * @brief Nạp các file âm thanh cần thiết.
         */
        void load();

        /**
         * @brief Phát âm thanh vỗ cánh khi chim nhảy.
         */
        void playFlap();

        /**
         * @brief Phát âm thanh ghi điểm khi chim vượt qua ống.
         */
        void playScore();

        /**
         * @brief Phát âm thanh va chạm khi chim đâm vào vật cản.
         */
        void playHit();

    private:
        sf::SoundBuffer m_flapBuffer;  /**< Bộ nhớ đệm cho âm thanh vỗ cánh */
        sf::SoundBuffer m_scoreBuffer; /**< Bộ nhớ đệm cho âm thanh ghi điểm */
        sf::SoundBuffer m_hitBuffer;   /**< Bộ nhớ đệm cho âm thanh va chạm */

        sf::Sound m_flapSound;   /**< Hiệu ứng âm thanh vỗ cánh */
        sf::Sound m_scoreSound;  /**< Hiệu ứng âm thanh ghi điểm */
        sf::Sound m_hitSound;    /**< Hiệu ứng âm thanh va chạm */
    };
}
