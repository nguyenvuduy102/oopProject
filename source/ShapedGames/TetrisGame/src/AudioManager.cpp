#include "../include/AudioManager.h"
#include <filesystem>

namespace Tetris
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

        fs::path p2 = fs::current_path() / ("../" + rel);
        if (fs::exists(p2))
            return p2.string();
        return rel;
    }

    /**
     * @brief Constructs an AudioManager, loading sound effects and background music.
     * @throws std::runtime_error If any audio file fails to load.
     */
    AudioManager::AudioManager()
        : rotateSound(rotateBuffer),
          clearSound(clearBuffer),
          gameOverSound(gameOverBuffer)
    {
        if (!LoadSound(rotateBuffer, TryPaths("../source/assets/sounds/rotate.ogg")))
            throw std::runtime_error("Failed to load rotate.ogg");
        if (!LoadSound(clearBuffer, TryPaths("../source/assets/sounds/clear.ogg")))
            throw std::runtime_error("Failed to load clear.ogg");
        if (!LoadSound(gameOverBuffer, TryPaths("../source/assets/sounds/gameover.ogg")))
            throw std::runtime_error("Failed to load gameover.ogg");

        rotateSound.setBuffer(rotateBuffer);
        clearSound.setBuffer(clearBuffer);
        gameOverSound.setBuffer(gameOverBuffer);

        if (!music.openFromFile(TryPaths("../source/assets/sounds/music.ogg")))
            throw std::runtime_error("Failed to load music.ogg");
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
     * @brief Plays the "rotate" sound effect when a block is rotated.
     */
    void AudioManager::PlayRotate() { rotateSound.play(); }

    /**
     * @brief Plays the "clear" sound effect when rows are cleared.
     */
    void AudioManager::PlayClear() { clearSound.play(); }

    /**
     * @brief Plays the "game over" sound effect.
     */
    void AudioManager::PlayGameOver() { gameOverSound.play(); }

    /**
     * @brief Starts playing the background music if it is not already playing.
     */
    void AudioManager::PlayMusic()
    {
        if (music.getStatus() != sf::SoundSource::Status::Playing)
            music.play();
    }

    /**
     * @brief Stops the background music.
     */
    void AudioManager::StopMusic() { music.stop(); }

    /**
     * @brief Pauses the background music if it is playing.
     */
    void AudioManager::PauseMusic()
    {
        if (music.getStatus() == sf::SoundSource::Status::Playing)
            music.pause();
    }

    /**
     * @brief Resumes the background music if it is paused.
     */
    void AudioManager::ResumeMusic()
    {
        if (music.getStatus() == sf::SoundSource::Status::Paused)
            music.play();
    }
}