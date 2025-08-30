#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include <SFML/Graphics.hpp>

namespace Tetris
{
    /**
     * @brief Represents a Tetris block with multiple cells and rotation states.
     */
    class Block
    {
    public:
        /**
         * @brief Constructs a Block with default values.
         */
        Block();

        /**
         * @brief Draws the block on the render window with specified offsets.
         * @param window The SFML render window.
         * @param offsetX Horizontal offset for drawing.
         * @param offsetY Vertical offset for drawing.
         */
        void Draw(sf::RenderWindow &window, int offsetX, int offsetY) const;

        /**
         * @brief Moves the block by the specified number of rows and columns.
         * @param rows Number of rows to move (positive down, negative up).
         * @param columns Number of columns to move (positive right, negative left).
         */
        void Move(int rows, int columns);

        /**
         * @brief Gets the positions of the block's cells after applying offsets.
         * @return A vector of Position objects representing the cells.
         */
        std::vector<Position> GetCellPositions() const;

        /**
         * @brief Gets the raw positions of the block's cells without offsets.
         * @return A vector of Position objects representing the raw cells.
         */
        std::vector<Position> GetRawCellPositions() const;

        /**
         * @brief Rotates the block to the next rotation state.
         */
        void Rotate();

        /**
         * @brief Undoes the last rotation of the block.
         */
        void UndoRotation();

        int id;                                     ///< Block identifier (color index).
        std::map<int, std::vector<Position>> cells; ///< Cell positions for each rotation state.

    private:
        int cellSize;                  ///< Size of each cell (not used in current implementation).
        int rotationState;             ///< Current rotation state index.
        std::vector<sf::Color> colors; ///< Colors for cells (not used in current implementation).
        int rowOffset;                 ///< Row offset for block position.
        int columnOffset;              ///< Column offset for block position.
    };
}