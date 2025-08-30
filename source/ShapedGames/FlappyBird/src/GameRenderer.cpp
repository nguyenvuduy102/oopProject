#include "../include/GameRenderer.h"
#include <stdexcept>

namespace Flappy
{
    // Constructor, set up renderer with texture manager
    GameRenderer::GameRenderer(TextureManager &tex)
        : m_textures(tex),
          m_scoreText(m_font, "", 76),                 // Text for score
          m_pressC(m_font, "Press C to continue", 42), // Text for game over prompt
          m_background{
              sf::Sprite(tex.getBackground()), // Background sprites
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground()),
              sf::Sprite(tex.getBackground())},
          m_gameover(tex.getGameover()) // Game over sprite
    {
    }

    // Load font and setup sprites
    void GameRenderer::load()
    {
        // Try load font, crash if fail
        if (!m_font.openFromFile("../source/assets/fonts/flappy.ttf"))
            throw std::runtime_error("failed to load flappy.ttf");

        // Setup background sprites
        for (int i = 0; i < 6; ++i)
        {
            m_background[i].setScale({2.0f, 2.2f});        // Scale up background
            m_background[i].setPosition({i * 266.f, 0.f}); // Space them out
        }

        // Setup game over sprite
        m_gameover.setOrigin({96.f, 21.f});     // Center it
        m_gameover.setPosition({400.f, 200.f}); // Put in middle
        m_gameover.setScale({2.f, 2.f});        // Make it bigger

        // Setup score text
        m_scoreText.setFillColor(sf::Color::White); // White text
        m_scoreText.setPosition({20.f, 10.f});      // Top-left corner

        // Setup "press C" text
        m_pressC.setFillColor(sf::Color::White);          // White text
        sf::FloatRect bounds = m_pressC.getLocalBounds(); // Get text bounds
        m_pressC.setOrigin({bounds.size.x / 2.f, 0.f});   // Center horizontally
        m_pressC.setPosition({400.f, 300.f});             // Put below game over
    }

    // Draw game stuff to window
    void GameRenderer::render(sf::RenderWindow &window,
                              const Bird &bird,
                              const std::deque<Pipe> &pipes,
                              int score,
                              GameState state,
                              int frames)
    {
        window.clear(); // Clear window first

        // Draw all background sprites
        for (auto &bg : m_background)
            window.draw(bg);

        // Draw all pipes
        for (auto &pipe : pipes)
        {
            window.draw(pipe.upper()); // Draw upper pipe
            window.draw(pipe.lower()); // Draw lower pipe
        }

        // Draw bird
        window.draw(bird.sprite());

        // Update and draw score
        m_scoreText.setString(std::to_string(score)); // Set score text
        window.draw(m_scoreText);                     // Show score

        // If game over, show game over stuff
        if (state == GameState::Gameover)
        {
            window.draw(m_gameover); // Show game over image
            if (frames % 60 < 30)    // Blink "press C" text
                window.draw(m_pressC);
        }

        window.display(); // Show everything
    }
}