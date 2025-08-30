#include "../include/GameCore.h"

namespace Flappy
{
    // Constructor, setup game with texture and defaults
    GameCore::GameCore(TextureManager &tex)
        : m_textures(tex), m_bird(tex), m_rng(std::random_device{}()),
          m_score(0), m_gravity(0.35f), m_flapImpulse(-3.f),
          m_pipeInterval(2.5f), m_pipeGap(120.f), m_pipeSpeed(3.f), m_spawnTimer(0.f) {}

    // Init game with window size
    void GameCore::init(const sf::Vector2u &windowSize)
    {
        m_audio.load();    // Load sound stuff
        reset(windowSize); // Get game ready
    }

    // Update game, move bird and pipes
    void GameCore::update(const sf::Vector2u &windowSize, float delta, int frames)
    {
        m_bird.update(m_gravity, frames, true, true); // Move and animate bird
        m_spawnTimer += delta;                        // Track time for new pipe

        // Add pipe when time’s up
        if (m_spawnTimer >= m_pipeInterval)
        {
            spawnPipe(windowSize); // Make new pipe
            m_spawnTimer = 0.f;    // Reset timer
        }

        // Move all pipes
        for (auto &pipe : m_pipes)
            pipe.update(m_pipeSpeed); // Slide pipes left

        // Clear pipes off screen
        while (!m_pipes.empty() && m_pipes.front().isOffScreen())
            m_pipes.pop_front();

        // Check for score
        for (auto &pipe : m_pipes)
        {
            if (!pipe.hasScored() && pipe.upper().getPosition().x + pipe.upper().getGlobalBounds().size.x < m_bird.getPosition().x)
            {
                m_score++;           // Up score
                pipe.setScored();    // Mark pipe done
                m_audio.playScore(); // Play score sound
            }
        }

        // Check if bird crash
        if (checkCollision(windowSize))
        {
            m_audio.playHit(); // Play crash sound
            reset(windowSize); // Start over
        }
    }

    // Handle spacebar input
    void GameCore::handleInput(GameState state, GameState &newState)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // If space hit
        {
            if (state == GameState::Waiting)   // If game not started
                newState = GameState::Started; // Start it
            if (state == GameState::Started)   // If playing
            {
                m_bird.flap(m_flapImpulse); // Bird jump
                m_audio.playFlap();         // Play flap sound
            }
        }
    }

    // Add new pipe pair
    void GameCore::spawnPipe(const sf::Vector2u &windowSize)
    {
        std::uniform_int_distribution<int> dist(100, 400);                                                       // Random gap height
        int r = dist(m_rng);                                                                                     // Pick random y
        m_pipes.emplace_back((float)windowSize.x + 100.f, (float)r, m_pipeGap, m_textures, (float)windowSize.y); // Add pipe
    }

    // Check if bird hit something
    bool GameCore::checkCollision(const sf::Vector2u &windowSize)
    {
        if (m_bird.getPosition().y > windowSize.y) // If bird hit ground
            return true;

        // Check pipes
        for (auto &pipe : m_pipes)
        {
            if (m_bird.getBounds().findIntersection(pipe.upper().getGlobalBounds())) // Hit upper pipe
                return true;
            if (m_bird.getBounds().findIntersection(pipe.lower().getGlobalBounds())) // Hit lower pipe
                return true;
        }
        return false; // No crash
    }

    // Reset game state
    void GameCore::reset(const sf::Vector2u &windowSize)
    {
        m_bird.reset(windowSize); // Reset bird
        m_pipes.clear();          // Clear pipes
        m_score = 0;              // Reset score
        m_spawnTimer = 0.f;       // Reset pipe timer
    }
}