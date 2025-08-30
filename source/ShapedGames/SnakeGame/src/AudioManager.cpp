#include "../include/AudioManager.h"
#include <filesystem>
#include <iostream>

namespace Snake
{
    using std::string;
    namespace fs = std::filesystem;

    static string TryPaths(const string &rel)
    {
        fs::path p1 = fs::current_path() / rel;
        if (fs::exists(p1))
            return p1.string();

        fs::path p2 = fs::current_path() / ("../source/" + rel);
        if (fs::exists(p2))
            return p2.string();

        std::cerr << "⚠️ File not found: " << rel << "\n";
        return rel;
    }

    AudioManager::AudioManager()
    {
        if (!LoadSound(m_eatBuffer, TryPaths("../source/assets/sounds/eat.wav")))
            throw std::runtime_error("Failed to load eat.wav");
        if (!LoadSound(m_gameOverBuffer, TryPaths("../source/assets/sounds/gameover.wav")))
            throw std::runtime_error("Failed to load gameover.wav");

        m_eatSound = std::make_unique<sf::Sound>(m_eatBuffer);
        m_gameOverSound = std::make_unique<sf::Sound>(m_gameOverBuffer);

        if (!m_music.openFromFile(TryPaths("../source/assets/sounds/background.ogg")))
            throw std::runtime_error("Failed to load background.ogg");
        m_music.setLooping(true);
    }

    bool AudioManager::LoadSound(sf::SoundBuffer &buffer, const string &path)
    {
        return buffer.loadFromFile(path);
    }

    void AudioManager::PlayEat()
    {
        if (m_eatSound)
            m_eatSound->play();
    }
    void AudioManager::PlayGameOver()
    {
        if (m_gameOverSound)
            m_gameOverSound->play();
    }
    void AudioManager::PlayMusic()
    {
        if (m_music.getStatus() != sf::SoundSource::Status::Playing)
            m_music.play();
    }
    void AudioManager::StopMusic() { m_music.stop(); }
    void AudioManager::PauseMusic()
    {
        if (m_music.getStatus() == sf::SoundSource::Status::Playing)
            m_music.pause();
    }
    void AudioManager::ResumeMusic()
    {
        if (m_music.getStatus() == sf::SoundSource::Status::Paused)
            m_music.play();
    }
}
