#include "../include/blocks_factory.h"
#include "../include/block.h"
#include "../include/position.h"

namespace Tetris
{
    /**
     * @brief Represents an L-shaped block.
     */
    class LBlock : public Block
    {
    public:
        /**
         * @brief Constructs an LBlock with predefined cell positions.
         */
        LBlock()
        {
            id = 1;
            cells[0] = {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
            cells[1] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
            cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 0}};
            cells[3] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
            Move(0, 3);
        }
    };

    /**
     * @brief Represents a J-shaped block.
     */
    class JBlock : public Block
    {
    public:
        /**
         * @brief Constructs a JBlock with predefined cell positions.
         */
        JBlock()
        {
            id = 2;
            cells[0] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
            cells[1] = {{0, 1}, {0, 2}, {1, 1}, {2, 1}};
            cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
            cells[3] = {{0, 1}, {1, 1}, {2, 0}, {2, 1}};
            Move(0, 3);
        }
    };

    /**
     * @brief Represents an I-shaped block.
     */
    class IBlock : public Block
    {
    public:
        /**
         * @brief Constructs an IBlock with predefined cell positions.
         */
        IBlock()
        {
            id = 3;
            cells[0] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
            cells[1] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}};
            cells[2] = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
            cells[3] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
            Move(-1, 3);
        }
    };

    /**
     * @brief Represents an O-shaped block.
     */
    class OBlock : public Block
    {
    public:
        /**
         * @brief Constructs an OBlock with predefined cell positions.
         */
        OBlock()
        {
            id = 4;
            cells[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
            Move(0, 4);
        }
    };

    /**
     * @brief Represents an S-shaped block.
     */
    class SBlock : public Block
    {
    public:
        /**
         * @brief Constructs an SBlock with predefined cell positions.
         */
        SBlock()
        {
            id = 5;
            cells[0] = {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
            cells[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
            cells[2] = {{1, 1}, {1, 2}, {2, 0}, {2, 1}};
            cells[3] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
            Move(0, 3);
        }
    };

    /**
     * @brief Represents a T-shaped block.
     */
    class TBlock : public Block
    {
    public:
        /**
         * @brief Constructs a TBlock with predefined cell positions.
         */
        TBlock()
        {
            id = 6;
            cells[0] = {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
            cells[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 1}};
            cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
            cells[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}};
            Move(0, 3);
        }
    };

    /**
     * @brief Represents a Z-shaped block.
     */
    class ZBlock : public Block
    {
    public:
        /**
         * @brief Constructs a ZBlock with predefined cell positions.
         */
        ZBlock()
        {
            id = 7;
            cells[0] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
            cells[1] = {{0, 2}, {1, 1}, {1, 2}, {2, 1}};
            cells[2] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
            cells[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 0}};
            Move(0, 3);
        }
    };

    /**
     * @brief Creates a vector containing all types of Tetris blocks.
     * @return A vector of Block objects (one of each type).
     */
    std::vector<Block> MakeAllBlocks()
    {
        return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    }
}