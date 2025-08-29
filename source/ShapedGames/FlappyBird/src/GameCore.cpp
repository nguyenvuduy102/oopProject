#include "../include/GameCore.h"

namespace Flappy
{
    GameCore::GameCore(TextureManager &tex)
        : m_textures(tex), m_bird(tex), m_rng(std::random_device{}()),
          m_score(0), m_gravity(0.35f), m_flapImpulse(-3.f),
          m_pipeInterval(2.5f), m_pipeGap(120.f), m_pipeSpeed(3.f), m_spawnTimer(0.f) {}

    void GameCore::init(const sf::Vector2u &windowSize)
    {
        m_audio.load();
        reset(windowSize);
    }

    void GameCore::update(const sf::Vector2u &windowSize, float delta, int frames)
    {
        m_bird.update(m_gravity, frames, true, true);
        m_spawnTimer += delta;

        if (m_spawnTimer >= m_pipeInterval)
        {
            spawnPipe(windowSize);
            m_spawnTimer = 0.f;
        }

        for (auto &pipe : m_pipes)
            pipe.update(m_pipeSpeed);

        while (!m_pipes.empty() && m_pipes.front().isOffScreen())
            m_pipes.pop_front();

        for (auto &pipe : m_pipes)
        {
            if (!pipe.hasScored() && pipe.upper().getPosition().x + pipe.upper().getGlobalBounds().size.x < m_bird.getPosition().x)
            {
                m_score++;
                pipe.setScored();
                m_audio.playScore();
            }
        }

        if (checkCollision(windowSize))
        {
            m_audio.playHit();
            reset(windowSize);
        }
    }

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

    void GameCore::spawnPipe(const sf::Vector2u &windowSize)
    {
        std::uniform_int_distribution<int> dist(100, 400);
        int r = dist(m_rng);
        m_pipes.emplace_back((float)windowSize.x + 100.f, (float)r, m_pipeGap, m_textures, (float)windowSize.y);
    }

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

    void GameCore::reset(const sf::Vector2u &windowSize)
    {
        m_bird.reset(windowSize);
        m_pipes.clear();
        m_score = 0;
        m_spawnTimer = 0.f;
    }
}
