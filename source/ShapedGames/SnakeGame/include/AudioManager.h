#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>

namespace Snake
{
    class AudioManager
    {
    public:
        AudioManager(); // load tất cả âm thanh khi khởi tạo
        void PlayEat();
        void PlayGameOver();
        void PlayMusic();
        void StopMusic();
        void PauseMusic();
        void ResumeMusic();

    private:
        sf::Music m_music;
        std::unique_ptr<sf::Sound> m_eatSound;
        std::unique_ptr<sf::Sound> m_gameOverSound;
        sf::SoundBuffer m_eatBuffer;
        sf::SoundBuffer m_gameOverBuffer;

        bool LoadSound(sf::SoundBuffer &buffer, const std::string &path);
    };
}
