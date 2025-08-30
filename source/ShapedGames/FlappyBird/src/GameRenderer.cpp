#include "../include/GameRenderer.h"
#include <stdexcept>

namespace Flappy
{
    /**
     * @brief Construct a new GameRenderer.
     * 
     * Initializes renderer with the provided texture manager,
     * prepares score/game over text objects and background sprites.
     * 
     * @param tex Reference to the shared TextureManager.
     */
    GameRenderer::GameRenderer(TextureManager &tex)
        : m_textures(tex),
          m_scoreText(m_font, "", 76),
          m_pressC(m_font, "Press C to continue", 42),
          m_background{
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground())},
          m_gameover(tex.getGameover())
    {
    }

    /**
     * @brief Load font and configure sprites/text elements.
     * 
     * Sets up background tiling, game over screen, score text,
     * and blinking "Press C to continue" prompt.
     * 
     * @throws std::runtime_error If font fails to load.
     */
    void GameRenderer::load()
    {
        if (!m_font.openFromFile("../source/assets/fonts/flappy.ttf"))
            throw std::runtime_error("failed to load flappy.ttf");

        // Configure background sprites
        for (int i = 0; i < 6; ++i)
        {
            m_background[i].setScale({2.0f, 2.2f});
            m_background[i].setPosition({i * 266.f, 0.f});
        }

        // Configure game over sprite
        m_gameover.setOrigin({96.f, 21.f});
        m_gameover.setPosition({400.f, 200.f});
        m_gameover.setScale({2.f, 2.f});

        // Configure score text
        m_scoreText.setFillColor(sf::Color::White);
        m_scoreText.setPosition({20.f, 10.f});

        // Configure "Press C" prompt
        m_pressC.setFillColor(sf::Color::White);
        sf::FloatRect bounds = m_pressC.getLocalBounds();
        m_pressC.setOrigin({bounds.size.x / 2.f, 0.f});
        m_pressC.setPosition({400.f, 300.f});
    }

    /**
     * @brief Render the current frame to the window.
     * 
     * Draws background, pipes, bird, score, and overlays (game over screen).
     * 
     * @param window Render target window.
     * @param bird Reference to the Bird instance.
     * @param pipes Container of active pipes.
     * @param score Current score value.
     * @param state Current game state.
     * @param frames Global frame counter.
     */
    void GameRenderer::render(sf::RenderWindow &window,
                              const Bird &bird,
                              const std::deque<Pipe> &pipes,
                              int score,
                              GameState state,
                              int frames)
    {
        window.clear();

        // Draw background
        for (auto &bg : m_background)
            window.draw(bg);

        // Draw pipes
        for (auto &pipe : pipes)
        {
            window.draw(pipe.upper());
            window.draw(pipe.lower());
        }

        // Draw bird
        window.draw(bird.sprite());

        // Update and draw score
        m_scoreText.setString(std::to_string(score));
        window.draw(m_scoreText);

        // Draw game over screen if needed
        if (state == GameState::Gameover)
        {
            window.draw(m_gameover);
            if (frames % 60 < 30) // Blink "Press C"
                window.draw(m_pressC);
        }

        window.display();
    }
}
