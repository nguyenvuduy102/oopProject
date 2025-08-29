#include "../include/AudioManager.h"
#include <filesystem>

namespace Tetris
{
    using std::string;
    namespace fs = std::filesystem;

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

    AudioManager::AudioManager()
        : rotateSound(rotateBuffer),
          clearSound(clearBuffer),
          gameOverSound(gameOverBuffer)
    {
        if (!LoadSound(rotateBuffer, TryPaths("assets/music/rotate.ogg")))
            throw std::runtime_error("Failed to load rotate.ogg");
        if (!LoadSound(clearBuffer, TryPaths("assets/music/clear.ogg")))
            throw std::runtime_error("Failed to load clear.ogg");
        if (!LoadSound(gameOverBuffer, TryPaths("assets/music/gameover.ogg")))
            throw std::runtime_error("Failed to load gameover.ogg");

        rotateSound.setBuffer(rotateBuffer);
        clearSound.setBuffer(clearBuffer);
        gameOverSound.setBuffer(gameOverBuffer);

        if (!music.openFromFile(TryPaths("assets/music/music.ogg")))
            throw std::runtime_error("Failed to load music.ogg");
    }

    bool AudioManager::LoadSound(sf::SoundBuffer &buffer, const string &path)
    {
        return buffer.loadFromFile(path);
    }

    void AudioManager::PlayRotate() { rotateSound.play(); }
    void AudioManager::PlayClear() { clearSound.play(); }
    void AudioManager::PlayGameOver() { gameOverSound.play(); }
    void AudioManager::PlayMusic()
    {
        if (music.getStatus() != sf::SoundSource::Status::Playing)
            music.play();
    }
    void AudioManager::StopMusic() { music.stop(); }
    void AudioManager::PauseMusic()
    {
        if (music.getStatus() == sf::SoundSource::Status::Playing)
            music.pause();
    }

    void AudioManager::ResumeMusic()
    {
        if (music.getStatus() == sf::SoundSource::Status::Paused)
            music.play();
    }
}
