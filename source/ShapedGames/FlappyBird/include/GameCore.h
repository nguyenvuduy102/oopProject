#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include <deque>
#include <random>
#include "Bird.h"
#include "Pipe.h"
#include "AudioManager.h"
#include "TextureManager.h"

namespace Flappy
{
    // Enum for game states
    enum class GameState
    {
        Waiting, // Before game start
        Started, // Game running
        Gameover // Game ended
    };

    // GameCore class, handle main game logic
    class GameCore
    {
    public:
        // Constructor, take texture manager
        GameCore(TextureManager &tex);
        // Set up game with window size
        void init(const sf::Vector2u &windowSize);
        // Update game state, pipes, bird, etc
        void update(const sf::Vector2u &windowSize, float delta, int frames);
        // Handle user input, change state if needed
        void handleInput(GameState state, GameState &newState);
        // Get bird for updating
        Bird &bird() { return m_bird; }
        // Get bird for rendering
        const Bird &bird() const { return m_bird; }
        // Get pipes for rendering
        const std::deque<Pipe> &pipes() const { return m_pipes; }
        // Get current score
        int score() const { return m_score; }
        // Reset game to start over
        void reset(const sf::Vector2u &windowSize);

    private:
        TextureManager &m_textures; // Texture manager ref
        Bird m_bird;                // Bird object
        std::deque<Pipe> m_pipes;   // List of pipes
        AudioManager m_audio;       // Audio manager for sounds
        std::mt19937 m_rng;         // Random number generator
        int m_score;                // Current score
        float m_gravity;            // Gravity for bird
        float m_flapImpulse;        // Jump strength
        float m_pipeInterval;       // Time between pipes
        float m_pipeGap;            // Gap size between pipes
        float m_pipeSpeed;          // How fast pipes move
        float m_spawnTimer;         // Timer for spawning pipes
        // Add new pipe
        void spawnPipe(const sf::Vector2u &windowSize);
        // Check if bird hit pipe or ground
        bool checkCollision(const sf::Vector2u &windowSize);
    };
}