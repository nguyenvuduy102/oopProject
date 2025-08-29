#pragma once
#include <memory>
#include "IGame.h"
#include "GameFactory.h"

class GameManager
{
public:
    static GameManager &instance();
    void setSelected(int idx);
    int getSelected() const;
    std::unique_ptr<IGame> createSelectedGame() const;
    void loadSettings();
    void saveSettings() const;

private:
    GameManager();
    int selected = 0;
};
