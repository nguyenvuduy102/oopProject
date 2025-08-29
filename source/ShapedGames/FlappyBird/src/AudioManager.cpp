#include "../include/AudioManager.h"
#include <stdexcept>

namespace Flappy
{
    AudioManager::AudioManager() : m_flapSound(m_flapBuffer), m_hitSound(m_hitBuffer), m_scoreSound(m_scoreBuffer) {}

    void AudioManager::load()
    {
        if (!m_flapBuffer.loadFromFile("assets/music/flap.wav"))
            throw std::runtime_error("failed to load flap.wav");
        if (!m_scoreBuffer.loadFromFile("assets/music/FlappyScore.wav"))
            throw std::runtime_error("failed to load score.wav");
        if (!m_hitBuffer.loadFromFile("assets/music/crash.wav"))
            throw std::runtime_error("failed to load crash.wav");

        m_flapSound.setBuffer(m_flapBuffer);
        m_scoreSound.setBuffer(m_scoreBuffer);
        m_hitSound.setBuffer(m_hitBuffer);
    }

    void AudioManager::playFlap() { m_flapSound.play(); }
    void AudioManager::playScore() { m_scoreSound.play(); }
    void AudioManager::playHit() { m_hitSound.play(); }
}
