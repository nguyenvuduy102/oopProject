#include "../include/block.h"
#include "../include/colors.h"

namespace Tetris
{
    static constexpr int CELL = 28;

    /**
     * @brief Constructs a Block with default values.
     */
    Block::Block()
        : id(0), rotationState(0), rowOffset(0), columnOffset(0)
    {
    }

    /**
     * @brief Draws the block on the render window with specified offsets.
     * @param window The SFML render window.
     * @param offsetX Horizontal offset for drawing.
     * @param offsetY Vertical offset for drawing.
     */
    void Block::Draw(sf::RenderWindow &window, int offsetX, int offsetY) const
    {
        auto colors = GetCellColors();

        for (auto &p : GetCellPositions())
        {
            sf::RectangleShape cell({(float)CELL, (float)CELL});

            sf::Vector2u winSize = window.getSize();
            float boardWidth = 12 * CELL;
            float boardHeight = 20 * CELL;
            float startX = (winSize.x - boardWidth) / 2.f;  // căn giữa ngang
            float startY = (winSize.y - boardHeight) / 2.f; // căn giữa dọc

            cell.setPosition({startX + offsetX + p.column * CELL - 125.f,
                              startY + offsetY + p.row * CELL + 10.f});

            cell.setFillColor(colors[id]);
            cell.setOutlineThickness(1.f);
            cell.setOutlineColor(sf::Color::Black);

            window.draw(cell);
        }
    }

    /**
     * @brief Moves the block by the specified number of rows and columns.
     * @param rows Number of rows to move (positive down, negative up).
     * @param columns Number of columns to move (positive right, negative left).
     */
    void Block::Move(int rows, int columns)
    {
        rowOffset += rows;
        columnOffset += columns;
    }

    /**
     * @brief Gets the positions of the block's cells after applying offsets.
     * @return A vector of Position objects representing the cells.
     */
    std::vector<Position> Block::GetCellPositions() const
    {
        std::vector<Position> tiles = cells.at(rotationState);
        std::vector<Position> movedTiles;

        for (Position item : tiles)
        {
            Position newPos = Position(item.row + rowOffset,
                                       item.column + columnOffset);
            movedTiles.push_back(newPos);
        }

        return movedTiles;
    }

    /**
     * @brief Rotates the block to the next rotation state.
     */
    void Block::Rotate()
    {
        rotationState++;
        if (rotationState == (int)cells.size())
        {
            rotationState = 0;
        }
    }

    /**
     * @brief Undoes the last rotation of the block.
     */
    void Block::UndoRotation()
    {
        rotationState--;
        if (rotationState == -1)
        {
            rotationState = cells.size() - 1;
        }
    }

    /**
     * @brief Gets the raw positions of the block's cells without offsets.
     * @return A vector of Position objects representing the raw cells.
     */
    std::vector<Position> Block::GetRawCellPositions() const
    {
        return cells.at(rotationState);
    }
}