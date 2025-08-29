#pragma once
#include <SFML/Audio.hpp>

namespace Flappy
{
    class AudioManager
    {
    public:
        AudioManager();
        void load();
        void playFlap();
        void playScore();
        void playHit();

    private:
        sf::SoundBuffer m_flapBuffer;
        sf::SoundBuffer m_scoreBuffer;
        sf::SoundBuffer m_hitBuffer;
        sf::Sound m_flapSound;
        sf::Sound m_scoreSound;
        sf::Sound m_hitSound;
    };
}
