#include "../include/grid.h"
#include <iostream>

namespace Tetris
{
    Grid::Grid()
    {
        numRows = 20;
        numCols = 12;
        cellSize = 28;
        Initialize();
        colors = GetCellColors();
    }

    void Grid::Initialize()
    {
        for (int r = 0; r < numRows; ++r)
            for (int c = 0; c < numCols; ++c)
                grid[r][c] = 0;
    }

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
                cell.setPosition({(float)(LEFT_OFFSET + c * cellSize + 108.f),
                                  (float)(TOP_OFFSET + r * cellSize + 30.f)});
                cell.setFillColor(colors[id]);
                cell.setOutlineThickness(1.f);
                cell.setOutlineColor(sf::Color::Black);
                window.draw(cell);
            }
        }
    }

    bool Grid::IsCellOutside(int row, int col)
    {
        return !(row >= 0 && row < numRows && col >= 0 && col < numCols);
    }
    bool Grid::IsCellEmpty(int row, int col) { return grid[row][col] == 0; }

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
    bool Grid::IsRowFull(int row)
    {
        for (int c = 0; c < numCols; ++c)
            if (grid[row][c] == 0)
                return false;
        return true;
    }
    void Grid::ClearRow(int row)
    {
        for (int c = 0; c < numCols; ++c)
            grid[row][c] = 0;
    }
    void Grid::MoveRowDown(int row, int n)
    {
        for (int c = 0; c < numCols; ++c)
        {
            grid[row + n][c] = grid[row][c];
            grid[row][c] = 0;
        }
    }
}
