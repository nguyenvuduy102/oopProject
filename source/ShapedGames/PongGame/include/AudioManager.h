#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace Pong
{
    /**
     * @class AudioManager
     * @brief Manages game sounds such as bounce and score effects in Pong.
     */
    class AudioManager
    {
    public:
        /**
         * @brief Constructor for AudioManager.
         */
        AudioManager();

        /**
         * @brief Load all required sound files into memory.
         */
        void load();

        /**
         * @brief Play the bounce sound when the ball hits a paddle or wall.
         */
        void playBounce();

        /**
         * @brief Play the score sound when a player scores a point.
         */
        void playScore();

    private:
        sf::SoundBuffer m_bounceBuffer; ///< Sound buffer for bounce effect.
        sf::SoundBuffer m_scoreBuffer;  ///< Sound buffer for score effect.
        sf::Sound m_bounceSound;        ///< Sound object for bounce effect.
        sf::Sound m_scoreSound;         ///< Sound object for score effect.
    };
}
