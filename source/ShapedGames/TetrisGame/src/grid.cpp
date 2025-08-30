#include "../include/grid.h"
#include <iostream>

namespace Tetris
{
    /**
     * @brief Constructs a Grid with default dimensions and colors.
     */
    Grid::Grid()
    {
        numRows = 20;
        numCols = 12;
        cellSize = 28;

        Initialize();
        colors = GetCellColors();
    }

    /**
     * @brief Initializes the grid by setting all cells to empty (0).
     */
    void Grid::Initialize()
    {
        for (int r = 0; r < numRows; ++r)
        {
            for (int c = 0; c < numCols; ++c)
            {
                grid[r][c] = 0;
            }
        }
    }

    /**
     * @brief Draws the grid cells on the render window.
     * @param window The SFML render window.
     */
    void Grid::Draw(sf::RenderWindow &window)
    {
        static constexpr int LEFT_OFFSET = 12;
        static constexpr int TOP_OFFSET = -10;

        for (int r = 0; r < numRows; ++r)
        {
            for (int c = 0; c < numCols; ++c)
            {
                int id = grid[r][c];
                if (id == 0)
                    continue;

                sf::RectangleShape cell({(float)cellSize - 1, (float)cellSize - 1});
                sf::Vector2u winSize = window.getSize();

                float boardWidth = numCols * cellSize;
                float boardHeight = numRows * cellSize;
                float startX = (winSize.x - boardWidth) / 2.f;
                float startY = (winSize.y - boardHeight) / 2.f;

                cell.setPosition({startX + LEFT_OFFSET + c * cellSize - 125.f,
                                  startY + TOP_OFFSET + r * cellSize + 10.f});

                cell.setFillColor(colors[id]);
                cell.setOutlineThickness(1.f);
                cell.setOutlineColor(sf::Color::Black);

                window.draw(cell);
            }
        }
    }

    /**
     * @brief Checks if a cell is outside the grid boundaries.
     * @param row The row index.
     * @param col The column index.
     * @return True if outside, false otherwise.
     */
    bool Grid::IsCellOutside(int row, int col)
    {
        return !(row >= 0 && row < numRows && col >= 0 && col < numCols);
    }

    /**
     * @brief Checks if a cell is empty.
     * @param row The row index.
     * @param col The column index.
     * @return True if empty (0), false otherwise.
     */
    bool Grid::IsCellEmpty(int row, int col)
    {
        return grid[row][col] == 0;
    }

    /**
     * @brief Clears full rows and moves upper rows down.
     * @return The number of rows cleared.
     */
    int Grid::ClearFullRows()
    {
        int completed = 0;

        for (int r = numRows - 1; r >= 0; --r)
        {
            if (IsRowFull(r))
            {
                ClearRow(r);
                ++completed;
            }
            else if (completed > 0)
            {
                MoveRowDown(r, completed);
            }
        }

        return completed;
    }

    /**
     * @brief Checks if a row is completely full.
     * @param row The row index.
     * @return True if full, false otherwise.
     */
    bool Grid::IsRowFull(int row)
    {
        for (int c = 0; c < numCols; ++c)
        {
            if (grid[row][c] == 0)
                return false;
        }
        return true;
    }

    /**
     * @brief Clears all cells in a row.
     * @param row The row index.
     */
    void Grid::ClearRow(int row)
    {
        for (int c = 0; c < numCols; ++c)
        {
            grid[row][c] = 0;
        }
    }

    /**
     * @brief Moves a row down by a specified number of positions.
     * @param row The source row index.
     * @param n The number of positions to move down.
     */
    void Grid::MoveRowDown(int row, int n)
    {
        for (int c = 0; c < numCols; ++c)
        {
            grid[row + n][c] = grid[row][c];
            grid[row][c] = 0;
        }
    }
}