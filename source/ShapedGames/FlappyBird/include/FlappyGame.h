#pragma once // Stop multiple includes
#include "../../../GameMain/Core/include/IGame.h"
#include "GameCore.h"
#include "GameRenderer.h"
#include "TextureManager.h"

/**
 * @file FlappyGame.h
 * @brief Khai báo lớp FlappyGame, lớp chính điều khiển trò chơi Flappy Bird.
 */

namespace Flappy
{
    /**
     * @class FlappyGame
     * @brief Lớp chính của trò chơi Flappy Bird.
     *
     * Lớp này kế thừa từ IGame và quản lý toàn bộ vòng đời của game:
     * - Khởi tạo game
     * - Chạy vòng lặp game
     * - Dọn dẹp khi kết thúc
     * - Cung cấp tên trò chơi
     */
    class FlappyGame : public IGame
    {
    public:
        /**
         * @brief Constructor. Thiết lập các thành phần game.
         */
        FlappyGame();

        /**
         * @brief Khởi tạo trò chơi với cửa sổ render.
         * @param window Tham chiếu tới sf::RenderWindow để vẽ game.
         */
        void init(sf::RenderWindow &window) override;

        /**
         * @brief Chạy vòng lặp chính của trò chơi.
         * @param window Tham chiếu tới sf::RenderWindow để render khung hình.
         */
        void run(sf::RenderWindow &window) override;

        /**
         * @brief Giải phóng tài nguyên khi trò chơi kết thúc.
         */
        void cleanup() override;

        /**
         * @brief Lấy tên trò chơi.
         * @return Chuỗi chứa tên trò chơi ("Flappy Bird").
         */
        std::string name() const override { return "Flappy Bird"; }

    private:
        TextureManager m_textures; /**< Quản lý texture của trò chơi */
        GameCore *m_core;          /**< Xử lý logic game */
        GameRenderer *m_renderer;  /**< Xử lý render game */
    };
}
