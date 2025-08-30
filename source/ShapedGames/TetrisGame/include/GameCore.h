#pragma once
#include "grid.h"
#include "block.h"
#include <vector>

namespace Tetris
{
    /**
     * @brief Manages the core game logic for Tetris, including block movement and scoring.
     */
    class GameCore
    {
    public:
        /**
         * @brief Struct to hold the result of a block movement step.
         */
        struct StepResult
        {
            int rowsCleared = 0;   ///< Number of rows cleared.
            bool locked = false;   ///< True if the block was locked in place.
            bool gameOver = false; ///< True if the game is over.
        };

        /**
         * @brief Constructs a GameCore instance, initializing game state.
         */
        GameCore();

        /**
         * @brief Updates the game state (currently empty).
         */
        void Update();

        /**
         * @brief Moves the current block left if possible.
         */
        void MoveLeft();

        /**
         * @brief Moves the current block right if possible.
         */
        void MoveRight();

        /**
         * @brief Moves the current block down, handling locking and row clearing.
         * @return A StepResult struct with details on rows cleared and game over status.
         */
        StepResult MoveDown();

        /**
         * @brief Rotates the current block if possible.
         * @return True if rotation succeeded, false otherwise.
         */
        bool Rotate();

        /**
         * @brief Checks if the game is over.
         * @return True if game over, false otherwise.
         */
        bool IsGameOver() const;

        /**
         * @brief Gets the current score.
         * @return The score.
         */
        int GetScore() const;

        /**
         * @brief Gets the total lines cleared.
         * @return The number of lines cleared.
         */
        int GetLines() const;

        /**
         * @brief Gets the current level.
         * @return The level.
         */
        int GetLevel() const;

        /**
         * @brief Checks if the game is paused.
         * @return True if paused, false otherwise.
         */
        bool IsPaused() const;

        /**
         * @brief Toggles the pause state.
         */
        void TogglePause();

        /**
         * @brief Gets the next block.
         * @return Const reference to the next Block.
         */
        const Block &GetNextBlock() const;

        /**
         * @brief Gets the current block.
         * @return Const reference to the current Block.
         */
        const Block &GetCurrentBlock() const;

        /**
         * @brief Gets the game grid.
         * @return Reference to the Grid.
         */
        Grid &GetGrid();

        /**
         * @brief Resets the game to initial state.
         */
        void Reset();

    private:
        /**
         * @brief Gets a random block from the available blocks.
         * @return A random Block.
         */
        Block GetRandomBlock();

        /**
         * @brief Checks if the current block fits without overlapping occupied cells.
         * @return True if it fits, false otherwise.
         */
        bool BlockFits();

        /**
         * @brief Checks if the current block is outside the grid boundaries.
         * @return True if outside, false otherwise.
         */
        bool IsBlockOutside();

        /**
         * @brief Updates the score based on lines cleared and move down points.
         * @param linesCleared Number of lines cleared.
         * @param moveDownPoints Additional points for moving down.
         */
        void UpdateScore(int linesCleared, int moveDownPoints);

        /**
         * @brief Handles logic after rows are cleared, updating lines and level.
         * @param rows Number of rows cleared.
         */
        void OnRowsCleared(int rows);

        Grid grid;                 ///< The game grid.
        std::vector<Block> blocks; ///< Available blocks for random selection.
        Block currentBlock;        ///< The current active block.
        Block nextBlock;           ///< The next block to be played.
        int score;                 ///< Current score.
        int linesClearedTotal;     ///< Total lines cleared.
        int level;                 ///< Current level.
        bool paused;               ///< True if game is paused.
        bool gameOver;             ///< True if game is over.
    };
}