#pragma once
#include <vector>
#include "block.h"

namespace Tetris
{
    /**
     * @brief Creates a vector containing all types of Tetris blocks.
     * @return A vector of Block objects (one of each type).
     */
    std::vector<Block> MakeAllBlocks();
}