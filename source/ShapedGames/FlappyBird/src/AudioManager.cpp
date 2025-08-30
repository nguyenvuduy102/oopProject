#include "../include/AudioManager.h"
#include <stdexcept>

namespace Flappy
{
    // Constructor, setup sound with buffers
    AudioManager::AudioManager() : m_flapSound(m_flapBuffer), m_hitSound(m_hitBuffer), m_scoreSound(m_scoreBuffer) {}

    // Load sound files
    void AudioManager::load()
    {
        // Try load flap sound, crash if fail
        if (!m_flapBuffer.loadFromFile("../source/assets/sounds/flap.wav"))
            throw std::runtime_error("failed to load flap.wav");
        // Try load score sound
        if (!m_scoreBuffer.loadFromFile("../source/assets/sounds/FlappyScore.wav"))
            throw std::runtime_error("failed to load score.wav");
        // Try load hit sound
        if (!m_hitBuffer.loadFromFile("../source/assets/sounds/crash.wav"))
            throw std::runtime_error("failed to load crash.wav");

        // Set buffers to sounds
        m_flapSound.setBuffer(m_flapBuffer);
        m_scoreSound.setBuffer(m_scoreBuffer);
        m_hitSound.setBuffer(m_hitBuffer);
    }

    // Play flap sound
    void AudioManager::playFlap() { m_flapSound.play(); }
    // Play score sound
    void AudioManager::playScore() { m_scoreSound.play(); }
    // Play hit sound
    void AudioManager::playHit() { m_hitSound.play(); }
}