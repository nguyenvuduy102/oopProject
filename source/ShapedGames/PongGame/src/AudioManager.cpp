#include "../include/AudioManager.h"

namespace Pong
{
    /**
     * @brief Construct a new AudioManager object.
     *
     * Initializes the sound objects with their respective buffers.
     */
    AudioManager::AudioManager() : m_bounceSound(m_bounceBuffer), m_scoreSound(m_scoreBuffer) {}

    /**
     * @brief Load audio resources for the Pong game.
     *
     * Loads the bounce and score sound effects from disk and associates
     * them with their sound buffers. Throws an exception if loading fails.
     *
     * @throws std::runtime_error if any audio file cannot be loaded.
     */
    void AudioManager::load()
    {
        if (!m_bounceBuffer.loadFromFile("../source/assets/sounds/bounce.wav"))
            throw std::runtime_error("Failed to load bounce.wav");
        if (!m_scoreBuffer.loadFromFile("../source/assets/sounds/score.wav"))
            throw std::runtime_error("Failed to load score.wav");

        m_bounceSound.setBuffer(m_bounceBuffer);
        m_scoreSound.setBuffer(m_scoreBuffer);
    }

    /**
     * @brief Play the bounce sound effect.
     */
    void AudioManager::playBounce()
    {
        m_bounceSound.play();
    }

    /**
     * @brief Play the score sound effect.
     */
    void AudioManager::playScore()
    {
        m_scoreSound.play();
    }
}
