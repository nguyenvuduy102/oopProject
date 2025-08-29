#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace Tetris
{
    class AudioManager
    {
    public:
        AudioManager();
        void PlayRotate();
        void PlayClear();
        void PlayGameOver();
        void PlayMusic();
        void StopMusic();
        void PauseMusic();
        void ResumeMusic();

    private:
        sf::SoundBuffer rotateBuffer;
        sf::SoundBuffer clearBuffer;
        sf::SoundBuffer gameOverBuffer;
        sf::Sound rotateSound;
        sf::Sound clearSound;
        sf::Sound gameOverSound;
        sf::Music music;

        bool LoadSound(sf::SoundBuffer &buffer, const std::string &path);
    };
}
