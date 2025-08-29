#include "../include/GameCore.h"
#include "../include/blocks_factory.h"
#include <cstdlib>
#include <algorithm>

namespace Tetris
{
    GameCore::GameCore()
        : score(0), linesClearedTotal(0), level(1), paused(false), gameOver(false)
    {
        grid = Grid();
        blocks = MakeAllBlocks();
        currentBlock = GetRandomBlock();
        nextBlock = GetRandomBlock();
    }

    void GameCore::Update()
    {
    }

    bool GameCore::IsGameOver() const { return gameOver; }
    int GameCore::GetScore() const { return score; }
    int GameCore::GetLines() const { return linesClearedTotal; }
    int GameCore::GetLevel() const { return level; }
    bool GameCore::IsPaused() const { return paused; }
    void GameCore::TogglePause() { paused = !paused; }

    const Block &GameCore::GetNextBlock() const { return nextBlock; }
    const Block &GameCore::GetCurrentBlock() const { return currentBlock; }
    Grid &GameCore::GetGrid() { return grid; }

    void GameCore::Reset()
    {
        grid.Initialize();
        blocks = MakeAllBlocks();
        currentBlock = GetRandomBlock();
        nextBlock = GetRandomBlock();
        score = 0;
        linesClearedTotal = 0;
        level = 1;
        paused = false;
        gameOver = false;
    }

    void GameCore::MoveLeft()
    {
        if (gameOver || paused)
            return;
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, 1);
    }

    void GameCore::MoveRight()
    {
        if (gameOver || paused)
            return;
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, -1);
    }

    GameCore::StepResult GameCore::MoveDown()
    {
        StepResult r{};
        if (gameOver || paused)
            return r;

        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            for (auto p : currentBlock.GetCellPositions())
                grid.grid[p.row][p.column] = currentBlock.id;

            currentBlock = nextBlock;
            if (!BlockFits())
            {
                gameOver = true;
                r.gameOver = true;
                return r;
            }
            nextBlock = GetRandomBlock();

            int rowsCleared = grid.ClearFullRows();
            if (rowsCleared > 0)
            {
                UpdateScore(rowsCleared, 0);
                OnRowsCleared(rowsCleared);
            }
            r.locked = true;
            r.rowsCleared = rowsCleared;
        }
        return r;
    }

    bool GameCore::Rotate()
    {
        if (gameOver || paused)
            return false;

        currentBlock.Rotate();
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.UndoRotation();
            return false;
        }
        return true;
    }

    Block GameCore::GetRandomBlock()
    {
        if (blocks.empty())
            blocks = MakeAllBlocks();

        int idx = std::rand() % static_cast<int>(blocks.size());
        Block b = blocks[idx];
        blocks.erase(blocks.begin() + idx);
        return b;
    }

    bool GameCore::IsBlockOutside()
    {
        for (auto p : currentBlock.GetCellPositions())
            if (grid.IsCellOutside(p.row, p.column))
                return true;
        return false;
    }

    bool GameCore::BlockFits()
    {
        for (auto p : currentBlock.GetCellPositions())
            if (!grid.IsCellEmpty(p.row, p.column))
                return false;
        return true;
    }

    void GameCore::UpdateScore(int linesCleared, int moveDownPoints)
    {
        switch (linesCleared)
        {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 800;
            break;
        default:
            break;
        }
        score += moveDownPoints;
    }

    void GameCore::OnRowsCleared(int rows)
    {
        if (rows <= 0)
            return;
        linesClearedTotal += rows;
        int newLevel = std::max(1, linesClearedTotal / 10 + 1);
        if (newLevel != level)
            level = newLevel;
    }
}