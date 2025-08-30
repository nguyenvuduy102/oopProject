#include "../include/block.h"
#include "../include/colors.h"

namespace Tetris
{
    static constexpr int CELL = 28;

    Block::Block()
        : id(0), rotationState(0), rowOffset(0), columnOffset(0)
    {
    }

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

    void Block::Move(int rows, int columns)
    {
        rowOffset += rows;
        columnOffset += columns;
    }

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

    void Block::Rotate()
    {
        rotationState++;
        if (rotationState == (int)cells.size())
        {
            rotationState = 0;
        }
    }

    void Block::UndoRotation()
    {
        rotationState--;
        if (rotationState == -1)
        {
            rotationState = cells.size() - 1;
        }
    }

    std::vector<Position> Block::GetRawCellPositions() const
    {
        return cells.at(rotationState);
    }
}
