#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include <SFML/Graphics.hpp>

namespace Tetris
{
    class Block
    {
    public:
        Block();
        void Draw(sf::RenderWindow &window, int offsetX, int offsetY) const;
        void Move(int rows, int columns);
        std::vector<Position> GetCellPositions() const;
        std::vector<Position> GetRawCellPositions() const;
        void Rotate();
        void UndoRotation();
        int id;
        std::map<int, std::vector<Position>> cells;

    private:
        int cellSize;
        int rotationState;
        std::vector<sf::Color> colors;
        int rowOffset;
        int columnOffset;
    };
}