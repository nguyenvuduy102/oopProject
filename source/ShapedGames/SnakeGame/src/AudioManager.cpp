#include "../include/AudioManager.h"
#include <filesystem>
#include <iostream>

namespace Snake
{
    using std::string;
    namespace fs = std::filesystem;

    /**
     * @brief Attempts to locate a file by trying multiple paths.
     * @param rel Relative path to the file.
     * @return Absolute path to the file if found, otherwise the original relative path.
     */
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

    /**
     * @brief Constructs an AudioManager, loading sound effects and background music.
     * @throws std::runtime_error If any audio file fails to load.
     */
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

    /**
     * @brief Loads a sound file into a sound buffer.
     * @param buffer The sound buffer to load the audio into.
     * @param path The file path to the sound file.
     * @return True if the sound was loaded successfully, false otherwise.
     */
    bool AudioManager::LoadSound(sf::SoundBuffer &buffer, const string &path)
    {
        return buffer.loadFromFile(path);
    }

    /**
     * @brief Plays the "eat" sound effect when the snake consumes food.
     */
    void AudioManager::PlayEat()
    {
        if (m_eatSound)
            m_eatSound->play();
    }

    /**
     * @brief Plays the "game over" sound effect.
     */
    void AudioManager::PlayGameOver()
    {
        if (m_gameOverSound)
            m_gameOverSound->play();
    }

    /**
     * @brief Starts playing the background music if it is not already playing.
     */
    void AudioManager::PlayMusic()
    {
        if (m_music.getStatus() != sf::SoundSource::Status::Playing)
            m_music.play();
    }

    /**
     * @brief Stops the background music.
     */
    void AudioManager::StopMusic() { m_music.stop(); }

    /**
     * @brief Pauses the background music if it is playing.
     */
    void AudioManager::PauseMusic()
    {
        if (m_music.getStatus() == sf::SoundSource::Status::Playing)
            m_music.pause();
    }

    /**
     * @brief Resumes the background music if it is paused.
     */
    void AudioManager::ResumeMusic()
    {
        if (m_music.getStatus() == sf::SoundSource::Status::Paused)
            m_music.play();
    }
}