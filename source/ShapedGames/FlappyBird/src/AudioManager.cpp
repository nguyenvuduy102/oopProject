#include "../include/AudioManager.h"
#include <stdexcept>

namespace Flappy
{
    /**
     * @brief Constructor. Initializes sound objects with their respective buffers.
     */
    AudioManager::AudioManager()
        : m_flapSound(m_flapBuffer),
          m_hitSound(m_hitBuffer),
          m_scoreSound(m_scoreBuffer) {}

    /**
     * @brief Load all sound files required for the game.
     *
     * Loads:
     * - Flap sound
     * - Score sound
     * - Hit sound
     *
     * @throws std::runtime_error If any sound file fails to load.
     */
    void AudioManager::load()
    {
        // Load flap sound
        if (!m_flapBuffer.loadFromFile("../source/assets/sounds/flap.wav"))
            throw std::runtime_error("Failed to load flap.wav");

        // Load score sound
        if (!m_scoreBuffer.loadFromFile("../source/assets/sounds/FlappyScore.wav"))
            throw std::runtime_error("Failed to load FlappyScore.wav");

        // Load hit sound
        if (!m_hitBuffer.loadFromFile("../source/assets/sounds/crash.wav"))
            throw std::runtime_error("Failed to load crash.wav");

        // Assign buffers to sounds
        m_flapSound.setBuffer(m_flapBuffer);
        m_scoreSound.setBuffer(m_scoreBuffer);
        m_hitSound.setBuffer(m_hitBuffer);
    }

    /**
     * @brief Play the flap sound effect.
     */
    void AudioManager::playFlap()
    {
        m_flapSound.play();
    }

    /**
     * @brief Play the score sound effect.
     */
    void AudioManager::playScore()
    {
        m_scoreSound.play();
    }

    /**
     * @brief Play the hit sound effect.
     */
    void AudioManager::playHit()
    {
        m_hitSound.play();
    }
}
