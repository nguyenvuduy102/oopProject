#include "../include/AudioManager.h"

namespace Pong
{
    AudioManager::AudioManager() : m_bounceSound(m_bounceBuffer), m_scoreSound(m_scoreBuffer) {}

    void AudioManager::load()
    {
        if (!m_bounceBuffer.loadFromFile("assets/music/bounce.wav"))
            throw std::runtime_error("Failed to load bounce.wav");
        if (!m_scoreBuffer.loadFromFile("assets/music/score.wav"))
            throw std::runtime_error("Failed to load score.wav");

        m_bounceSound.setBuffer(m_bounceBuffer);
        m_scoreSound.setBuffer(m_scoreBuffer);
    }

    void AudioManager::playBounce()
    {
        m_bounceSound.play();
    }

    void AudioManager::playScore()
    {
        m_scoreSound.play();
    }
}
