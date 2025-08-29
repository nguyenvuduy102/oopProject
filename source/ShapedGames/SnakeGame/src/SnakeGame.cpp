#include "../include/SnakeGame.h"
#include <filesystem>
#include <iostream>

namespace Snake
{
    static std::string TryPaths(const std::string &rel)
    {
        namespace fs = std::filesystem;

        // 1. Thử ngay tại working directory (release/assets/...)
        fs::path p1 = fs::current_path() / rel;
        if (fs::exists(p1))
            return p1.string();

        // 2. Thử nhảy lên source/assets/... (khi chạy từ release/)
        fs::path p2 = fs::current_path() / "../source" / rel;
        if (fs::exists(p2))
            return p2.string();
        fs::path p3 = fs::current_path() / "../release" / rel;
        if (fs::exists(p3))
            return p3.string();

        std::cerr << "⚠️ File not found: " << rel << "\n";
        return rel; // fallback
    }

    SnakeGame::SnakeGame()
        : m_controller(m_audio)
    {
    }

    void SnakeGame::init(sf::RenderWindow &window)
    {
        if (m_initialized)
            return;

        m_renderer = new GameRenderer(window);
        m_audio.PlayMusic();
        m_initialized = true;
    }

    void SnakeGame::run(sf::RenderWindow &window)
    {
        init(window);
        while (window.isOpen())
        {
            while (auto ev = window.pollEvent())
            {
                if (ev->is<sf::Event::Closed>())
                    window.close();

                m_controller.handleEvent(ev);

                if (m_controller.mode() == Mode::GameOver)
                {
                    if (auto key = ev->getIf<sf::Event::KeyPressed>())
                        if (key->code == sf::Keyboard::Key::Escape)
                            return;
                }
            }

            m_controller.update();
            m_renderer->render(m_controller);
        }
    }

    void SnakeGame::cleanup()
    {
        m_audio.StopMusic();
        if (m_renderer)
        {
            delete m_renderer;
            m_renderer = nullptr;
        }
        m_initialized = false;
    }
}
