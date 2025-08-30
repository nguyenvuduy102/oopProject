#include "../include/GameCore.h"

namespace Flappy
{
    /**
     * @brief Construct a new GameCore instance with default values.
     * 
     * Initializes bird, physics settings, and pipe parameters.
     * @param tex Reference to the shared TextureManager.
     */
    GameCore::GameCore(TextureManager &tex)
        : m_textures(tex), m_bird(tex), m_rng(std::random_device{}()),
          m_score(0), m_gravity(0.35f), m_flapImpulse(-3.f),
          m_pipeInterval(2.5f), m_pipeGap(150.f), m_pipeSpeed(3.f), m_spawnTimer(0.f) {}

    /**
     * @brief Initialize the game with the given window size.
     * 
     * Loads audio assets and resets the game state.
     * @param windowSize The size of the render window.
     */
    void GameCore::init(const sf::Vector2u &windowSize)
    {
        m_audio.load();
        reset(windowSize);
    }

    /**
     * @brief Update the game state each frame.
     * 
     * Moves the bird, spawns pipes, updates positions, checks scoring,
     * and detects collisions.
     * 
     * @param windowSize Current window dimensions.
     * @param delta Time since last frame in seconds.
     * @param frames Frame counter.
     */
    void GameCore::update(const sf::Vector2u &windowSize, float delta, int frames)
    {
        m_bird.update(m_gravity, frames, true, true);
        m_spawnTimer += delta;

        // Spawn new pipe when interval reached
        if (m_spawnTimer >= m_pipeInterval)
        {
            spawnPipe(windowSize);
            m_spawnTimer = 0.f;
        }

        // Update pipe positions
        for (auto &pipe : m_pipes)
            pipe.update(m_pipeSpeed);

        // Remove off-screen pipes
        while (!m_pipes.empty() && m_pipes.front().isOffScreen())
            m_pipes.pop_front();

        // Handle scoring
        for (auto &pipe : m_pipes)
        {
            if (!pipe.hasScored() &&
                pipe.upper().getPosition().x + pipe.upper().getGlobalBounds().size.x < m_bird.getPosition().x)
            {
                m_score++;
                pipe.setScored();
                m_audio.playScore();
            }
        }

        // Handle collisions
        if (checkCollision(windowSize))
        {
            m_audio.playHit();
            reset(windowSize);
        }
    }

    /**
     * @brief Handle player input.
     * 
     * Spacebar starts the game from waiting state or makes the bird flap
     * during gameplay.
     * 
     * @param state Current game state.
     * @param newState State to update if input changes it.
     */
    void GameCore::handleInput(GameState state, GameState &newState)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            if (state == GameState::Waiting)
                newState = GameState::Started;

            if (state == GameState::Started)
            {
                m_bird.flap(m_flapImpulse);
                m_audio.playFlap();
            }
        }
    }

    /**
     * @brief Spawn a new pair of pipes at a random vertical position.
     * 
     * @param windowSize Dimensions of the render window.
     */
    void GameCore::spawnPipe(const sf::Vector2u &windowSize)
    {
        std::uniform_int_distribution<int> dist(100, 400);
        int r = dist(m_rng);
        m_pipes.emplace_back(
            static_cast<float>(windowSize.x) + 100.f,
            static_cast<float>(r),
            m_pipeGap,
            m_textures,
            static_cast<float>(windowSize.y));
    }

    /**
     * @brief Check whether the bird has collided with the ground or a pipe.
     * 
     * @param windowSize Dimensions of the render window.
     * @return true if collision detected, false otherwise.
     */
    bool GameCore::checkCollision(const sf::Vector2u &windowSize)
    {
        if (m_bird.getPosition().y > windowSize.y)
            return true;

        for (auto &pipe : m_pipes)
        {
            if (m_bird.getBounds().findIntersection(pipe.upper().getGlobalBounds()))
                return true;
            if (m_bird.getBounds().findIntersection(pipe.lower().getGlobalBounds()))
                return true;
        }
        return false;
    }

    /**
     * @brief Reset the game to its initial state.
     * 
     * Resets the bird, clears all pipes, and resets score and timers.
     * 
     * @param windowSize Current window size.
     */
    void GameCore::reset(const sf::Vector2u &windowSize)
    {
        m_bird.reset(windowSize);
        m_pipes.clear();
        m_score = 0;
        m_spawnTimer = 0.f;
    }
}
