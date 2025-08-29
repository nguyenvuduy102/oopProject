#pragma once
#include <memory>
#include <vector>
#include <string>
#include "IGame.h"

class GameFactory
{
public:
    enum GameId
    {
        TETRIS = 0,
        SNAKE,
        PONG,
        FLAPPY
    };

    static std::unique_ptr<IGame> create(GameId id);
    static std::vector<std::string> gameNames();
};
