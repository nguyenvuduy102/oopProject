#include "../include/GameCore.h"
#include "../include/blocks_factory.h"
#include <cstdlib>
#include <algorithm>

namespace Tetris
{
    /**
     * @brief Constructs a GameCore instance, initializing game state.
     */
    GameCore::GameCore()
        : score(0), linesClearedTotal(0), level(1), paused(false), gameOver(false)
    {
        grid = Grid();
        blocks = MakeAllBlocks();
        currentBlock = GetRandomBlock();
        nextBlock = GetRandomBlock();
    }

    /**
     * @brief Updates the game state (currently empty).
     */
    void GameCore::Update()
    {
    }

    /**
     * @brief Checks if the game is over.
     * @return True if game over, false otherwise.
     */
    bool GameCore::IsGameOver() const { return gameOver; }

    /**
     * @brief Gets the current score.
     * @return The score.
     */
    int GameCore::GetScore() const { return score; }

    /**
     * @brief Gets the total lines cleared.
     * @return The number of lines cleared.
     */
    int GameCore::GetLines() const { return linesClearedTotal; }

    /**
     * @brief Gets the current level.
     * @return The level.
     */
    int GameCore::GetLevel() const { return level; }

    /**
     * @brief Checks if the game is paused.
     * @return True if paused, false otherwise.
     */
    bool GameCore::IsPaused() const { return paused; }

    /**
     * @brief Toggles the pause state.
     */
    void GameCore::TogglePause() { paused = !paused; }

    /**
     * @brief Gets the next block.
     * @return Const reference to the next Block.
     */
    const Block &GameCore::GetNextBlock() const { return nextBlock; }

    /**
     * @brief Gets the current block.
     * @return Const reference to the current Block.
     */
    const Block &GameCore::GetCurrentBlock() const { return currentBlock; }

    /**
     * @brief Gets the game grid.
     * @return Reference to the Grid.
     */
    Grid &GameCore::GetGrid() { return grid; }

    /**
     * @brief Resets the game to initial state.
     */
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

    /**
     * @brief Moves the current block left if possible.
     */
    void GameCore::MoveLeft()
    {
        if (gameOver || paused)
            return;
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, 1);
    }

    /**
     * @brief Moves the current block right if possible.
     */
    void GameCore::MoveRight()
    {
        if (gameOver || paused)
            return;
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, -1);
    }

    /**
     * @brief Moves the current block down, handling locking and row clearing.
     * @return A StepResult struct with details on rows cleared and game over status.
     */
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

    /**
     * @brief Rotates the current block if possible.
     * @return True if rotation succeeded, false otherwise.
     */
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

    /**
     * @brief Gets a random block from the available blocks.
     * @return A random Block.
     */
    Block GameCore::GetRandomBlock()
    {
        if (blocks.empty())
            blocks = MakeAllBlocks();

        int idx = std::rand() % static_cast<int>(blocks.size());
        Block b = blocks[idx];
        blocks.erase(blocks.begin() + idx);
        return b;
    }

    /**
     * @brief Checks if the current block is outside the grid boundaries.
     * @return True if outside, false otherwise.
     */
    bool GameCore::IsBlockOutside()
    {
        for (auto p : currentBlock.GetCellPositions())
            if (grid.IsCellOutside(p.row, p.column))
                return true;
        return false;
    }

    /**
     * @brief Checks if the current block fits without overlapping occupied cells.
     * @return True if it fits, false otherwise.
     */
    bool GameCore::BlockFits()
    {
        for (auto p : currentBlock.GetCellPositions())
            if (!grid.IsCellEmpty(p.row, p.column))
                return false;
        return true;
    }

    /**
     * @brief Updates the score based on lines cleared and move down points.
     * @param linesCleared Number of lines cleared.
     * @param moveDownPoints Additional points for moving down.
     */
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

    /**
     * @brief Handles logic after rows are cleared, updating lines and level.
     * @param rows Number of rows cleared.
     */
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