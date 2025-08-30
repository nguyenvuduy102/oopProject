#pragma once // Stop multiple includes
#include <SFML/Audio.hpp>

namespace Flappy
{
    // AudioManager class, handle sounds for Flappy Bird
    class AudioManager
    {
    public:
        // Constructor, set up audio stuff
        AudioManager();
        // Load sound files
        void load();
        // Play flap sound when bird jump
        void playFlap();
        // Play score sound when pass pipe
        void playScore();
        // Play hit sound when crash
        void playHit();

    private:
        sf::SoundBuffer m_flapBuffer;  // Buffer for flap sound
        sf::SoundBuffer m_scoreBuffer; // Buffer for score sound
        sf::SoundBuffer m_hitBuffer;   // Buffer for hit sound
        sf::Sound m_flapSound;         // Flap sound effect
        sf::Sound m_scoreSound;        // Score sound effect
        sf::Sound m_hitSound;          // Hit sound effect
    };
}