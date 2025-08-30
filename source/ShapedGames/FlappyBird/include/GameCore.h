#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include <deque>
#include <random>
#include "Bird.h"
#include "Pipe.h"
#include "AudioManager.h"
#include "TextureManager.h"

/**
 * @file GameCore.h
 * @brief Khai báo lớp GameCore, xử lý logic chính của trò chơi Flappy Bird.
 */

namespace Flappy
{
    /**
     * @enum GameState
     * @brief Trạng thái của trò chơi.
     */
    enum class GameState
    {
        Waiting, /**< Trước khi trò chơi bắt đầu */
        Started, /**< Trò chơi đang chạy */
        Gameover /**< Trò chơi đã kết thúc */
    };

    /**
     * @class GameCore
     * @brief Lớp xử lý toàn bộ logic của game Flappy Bird.
     *
     * Chức năng chính:
     * - Quản lý chim (Bird), ống (Pipe), và âm thanh (AudioManager).
     * - Xử lý input, va chạm và tính điểm.
     * - Sinh pipe ngẫu nhiên và cập nhật trạng thái game.
     */
    class GameCore
    {
    public:
        /**
         * @brief Constructor.
         * @param tex Tham chiếu tới TextureManager để quản lý texture.
         */
        GameCore(TextureManager &tex);

        /**
         * @brief Khởi tạo game với kích thước cửa sổ.
         * @param windowSize Kích thước cửa sổ render.
         */
        void init(const sf::Vector2u &windowSize);

        /**
         * @brief Cập nhật trạng thái trò chơi.
         * @param windowSize Kích thước cửa sổ render.
         * @param delta Thời gian trôi qua giữa 2 frame (giây).
         * @param frames Số frame để điều khiển hoạt ảnh.
         */
        void update(const sf::Vector2u &windowSize, float delta, int frames);

        /**
         * @brief Xử lý input từ người chơi, thay đổi trạng thái nếu cần.
         * @param state Trạng thái hiện tại của game.
         * @param newState Trạng thái mới sau khi xử lý input.
         */
        void handleInput(GameState state, GameState &newState);

        /**
         * @brief Lấy chim (có thể chỉnh sửa).
         * @return Tham chiếu tới Bird.
         */
        Bird &bird() { return m_bird; }

        /**
         * @brief Lấy chim (chỉ đọc).
         * @return Tham chiếu const tới Bird.
         */
        const Bird &bird() const { return m_bird; }

        /**
         * @brief Lấy danh sách ống.
         * @return Tham chiếu const tới deque chứa Pipe.
         */
        const std::deque<Pipe> &pipes() const { return m_pipes; }

        /**
         * @brief Lấy điểm hiện tại.
         * @return Điểm số của người chơi.
         */
        int score() const { return m_score; }

        /**
         * @brief Reset game về trạng thái ban đầu.
         * @param windowSize Kích thước cửa sổ render.
         */
        void reset(const sf::Vector2u &windowSize);

    private:
        TextureManager &m_textures; /**< Quản lý texture */
        Bird m_bird;                /**< Chim trong game */
        std::deque<Pipe> m_pipes;   /**< Danh sách ống */
        AudioManager m_audio;       /**< Quản lý âm thanh */
        std::mt19937 m_rng;         /**< Bộ sinh số ngẫu nhiên */
        int m_score;                /**< Điểm số hiện tại */
        float m_gravity;            /**< Trọng lực tác động lên chim */
        float m_flapImpulse;        /**< Độ mạnh khi chim vỗ cánh */
        float m_pipeInterval;       /**< Khoảng thời gian giữa các ống */
        float m_pipeGap;            /**< Khoảng cách giữa 2 ống */
        float m_pipeSpeed;          /**< Tốc độ di chuyển của ống */
        float m_spawnTimer;         /**< Bộ đếm thời gian để sinh ống */

        /**
         * @brief Sinh một ống mới.
         * @param windowSize Kích thước cửa sổ render.
         */
        void spawnPipe(const sf::Vector2u &windowSize);

        /**
         * @brief Kiểm tra va chạm của chim với ống hoặc mặt đất.
         * @param windowSize Kích thước cửa sổ render.
         * @return true nếu có va chạm, false nếu không.
         */
        bool checkCollision(const sf::Vector2u &windowSize);
    };
}
