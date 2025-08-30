#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace Tetris
{
    /**
     * @brief Manages audio resources for the Tetris game, including sound effects and background music.
     */
    class AudioManager
    {
    public:
        /**
         * @brief Constructs an AudioManager, loading all audio files.
         * @throws std::runtime_error If any audio file fails to load.
         */
        AudioManager();

        /**
         * @brief Plays the "rotate" sound effect when a block is rotated.
         */
        void PlayRotate();

        /**
         * @brief Plays the "clear" sound effect when rows are cleared.
         */
        void PlayClear();

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
         * @brief Pauses the background music if it is playing.
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

        sf::SoundBuffer rotateBuffer;   ///< Buffer for the rotate sound effect.
        sf::SoundBuffer clearBuffer;    ///< Buffer for the clear sound effect.
        sf::SoundBuffer gameOverBuffer; ///< Buffer for the game over sound effect.
        sf::Sound rotateSound;          ///< Sound effect for block rotation.
        sf::Sound clearSound;           ///< Sound effect for clearing rows.
        sf::Sound gameOverSound;        ///< Sound effect for game over.
        sf::Music music;                ///< Background music for the game.
    };
}