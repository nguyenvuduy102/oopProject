#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <random>
#include "Bird.h"
#include "Pipe.h"
#include "AudioManager.h"
#include "TextureManager.h"

namespace Flappy
{
    enum class GameState
    {
        Waiting,
        Started,
        Gameover
    };

    class GameCore
    {
    public:
        GameCore(TextureManager &tex);
        void init(const sf::Vector2u &windowSize);
        void update(const sf::Vector2u &windowSize, float delta, int frames);
        void handleInput(GameState state, GameState &newState);
        Bird &bird() { return m_bird; }
        const Bird &bird() const { return m_bird; }
        const std::deque<Pipe> &pipes() const { return m_pipes; }
        int score() const { return m_score; }
        void reset(const sf::Vector2u &windowSize);

    private:
        TextureManager &m_textures;
        Bird m_bird;
        std::deque<Pipe> m_pipes;
        AudioManager m_audio;
        std::mt19937 m_rng;
        int m_score;
        float m_gravity;
        float m_flapImpulse;
        float m_pipeInterval;
        float m_pipeGap;
        float m_pipeSpeed;
        float m_spawnTimer;
        void spawnPipe(const sf::Vector2u &windowSize);
        bool checkCollision(const sf::Vector2u &windowSize);
    };
}
