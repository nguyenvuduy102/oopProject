#pragma once
#include "grid.h"
#include "block.h"
#include <vector>

namespace Tetris
{
    class GameCore
    {
    public:
        struct StepResult
        {
            int rowsCleared = 0;
            bool locked = false;
            bool gameOver = false;
        };

        GameCore();

        void Update();
        void MoveLeft();
        void MoveRight();
        StepResult MoveDown(); // tick rơi xuống
        bool Rotate();         // true nếu xoay thành công

        bool IsGameOver() const;
        int GetScore() const;
        int GetLines() const;
        int GetLevel() const;
        bool IsPaused() const;
        void TogglePause();

        const Block &GetNextBlock() const;
        const Block &GetCurrentBlock() const;
        Grid &GetGrid();

        void Reset();

    private:
        Grid grid;
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;

        int score;
        int linesClearedTotal;
        int level;
        bool paused;
        bool gameOver;

        Block GetRandomBlock();
        bool BlockFits();
        bool IsBlockOutside();
        void UpdateScore(int linesCleared, int moveDownPoints);
        void OnRowsCleared(int rows);
    };
}