#include "../include/position.h"

namespace Tetris
{
    /**
     * @brief Constructs a Position with given row and column.
     * @param row The row index.
     * @param column The column index.
     */
    Position::Position(int row, int column)
    {
        this->row = row;
        this->column = column;
    }
}