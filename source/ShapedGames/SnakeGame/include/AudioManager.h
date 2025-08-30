#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>

namespace Snake
{
    /**
     * @brief Manages audio resources for the Snake game, including sound effects and background music.
     */
    class AudioManager
    {
    public:
        /**
         * @brief Constructs an AudioManager, loading all audio files (sound effects and music).
         * @throws std::runtime_error If any audio file fails to load.
         */
        AudioManager();

        /**
         * @brief Plays the "eat" sound effect when the snake consumes food.
         */
        void PlayEat();

        /**
         * @brief Plays the "game over" sound effect.
         */
        void PlayGameOver();

        /**
         * @brief Starts playing the background music if it is not already playing.
         */
        void PlayMusic();

        /**
         * @brief Stops the background music.
         */
        void StopMusic();

        /**
         * @brief Pauses the background music if it is currently playing.
         */
        void PauseMusic();

        /**
         * @brief Resumes the background music if it is paused.
         */
        void ResumeMusic();

    private:
        /**
         * @brief Loads a sound file into a sound buffer.
         * @param buffer The sound buffer to load the audio into.
         * @param path The file path to the sound file.
         * @return True if the sound was loaded successfully, false otherwise.
         */
        bool LoadSound(sf::SoundBuffer &buffer, const std::string &path);

        sf::Music m_music;                          ///< Background music for the game.
        std::unique_ptr<sf::Sound> m_eatSound;      ///< Sound effect for eating food.
        std::unique_ptr<sf::Sound> m_gameOverSound; ///< Sound effect for game over.
        sf::SoundBuffer m_eatBuffer;                ///< Buffer for the eat sound effect.
        sf::SoundBuffer m_gameOverBuffer;           ///< Buffer for the game over sound effect.
    };
}