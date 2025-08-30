#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "colors.h"

namespace Tetris
{
    /**
     * @brief Represents the Tetris game grid, managing cell states and rendering.
     */
    class Grid
    {
    public:
        /**
         * @brief Constructs a Grid with default dimensions and colors.
         */
        Grid();

        /**
         * @brief Initializes the grid by setting all cells to empty (0).
         */
        void Initialize();

        /**
         * @brief Draws the grid cells on the render window.
         * @param window The SFML render window.
         */
        void Draw(sf::RenderWindow &window);

        /**
         * @brief Checks if a cell is outside the grid boundaries.
         * @param row The row index.
         * @param column The column index.
         * @return True if outside, false otherwise.
         */
        bool IsCellOutside(int row, int column);

        /**
         * @brief Checks if a cell is empty.
         * @param row The row index.
         * @param column The column index.
         * @return True if empty (0), false otherwise.
         */
        bool IsCellEmpty(int row, int column);

        /**
         * @brief Clears full rows and moves upper rows down.
         * @return The number of rows cleared.
         */
        int ClearFullRows();

        int grid[20][12]; ///< 2D array representing the grid state (0 for empty, >0 for block ID).

    private:
        /**
         * @brief Checks if a row is completely full.
         * @param row The row index.
         * @return True if full, false otherwise.
         */
        bool IsRowFull(int row);

        /**
         * @brief Clears all cells in a row.
         * @param row The row index.
         */
        void ClearRow(int row);

        /**
         * @brief Moves a row down by a specified number of positions.
         * @param row The source row index.
         * @param numRows The number of positions to move down.
         */
        void MoveRowDown(int row, int numRows);

        int numRows;                   ///< Number of rows in the grid.
        int numCols;                   ///< Number of columns in the grid.
        int cellSize;                  ///< Size of each cell in pixels.
        std::vector<sf::Color> colors; ///< Colors for different block types.
    };
}