#pragma once // Prevent multiple includes
#include <SFML/Audio.hpp>

namespace Flappy
{
    /**
     * @class AudioManager
     * @brief Manages sound effects for the Flappy Bird game.
     *
     * This class is responsible for loading and playing the following sound effects:
     * - Flap sound when the bird jumps
     * - Score sound when the bird passes a pipe
     * - Hit sound when the bird collides with an obstacle
     */
    class AudioManager
    {
    public:
        /**
         * @brief Constructor.
         *
         * Initializes the AudioManager and prepares the sound objects.
         */
        AudioManager();

        /**
         * @brief Load all required sound files.
         *
         * Throws a runtime_error if a sound file fails to load.
         */
        void load();

        /**
         * @brief Play the flap sound when the bird jumps.
         */
        void playFlap();

        /**
         * @brief Play the score sound when the bird passes a pipe.
         */
        void playScore();

        /**
         * @brief Play the hit sound when the bird collides with an obstacle.
         */
        void playHit();

    private:
        sf::SoundBuffer m_flapBuffer;   /**< Buffer for the flap sound */
        sf::SoundBuffer m_scoreBuffer;  /**< Buffer for the score sound */
        sf::SoundBuffer m_hitBuffer;    /**< Buffer for the hit sound */

        sf::Sound m_flapSound;   /**< Flap sound effect */
        sf::Sound m_scoreSound;  /**< Score sound effect */
        sf::Sound m_hitSound;    /**< Hit sound effect */
    };
}
