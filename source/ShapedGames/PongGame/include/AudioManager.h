#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace Pong
{
    class AudioManager
    {
    public:
        AudioManager();
        void load();
        void playBounce();
        void playScore();

    private:
        sf::SoundBuffer m_bounceBuffer;
        sf::SoundBuffer m_scoreBuffer;
        sf::Sound m_bounceSound;
        sf::Sound m_scoreSound;
    };
}
