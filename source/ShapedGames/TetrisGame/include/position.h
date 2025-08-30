#pragma once

namespace Tetris
{
    /**
     * @brief Represents a position on the Tetris grid with row and column indices.
     */
    class Position
    {
    public:
        /**
         * @brief Constructs a Position with given row and column.
         * @param row The row index.
         * @param column The column index.
         */
        Position(int row, int column);

        int row;    ///< Row index.
        int column; ///< Column index.
    };
}