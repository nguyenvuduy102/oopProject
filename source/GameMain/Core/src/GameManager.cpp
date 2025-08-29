#include "../include/GameManager.h"
#include <fstream>

static const char *SETTINGS_FILE = "settings.txt";

GameManager &GameManager::instance()
{
    static GameManager inst;
    return inst;
}

GameManager::GameManager() { loadSettings(); }

void GameManager::setSelected(int idx)
{
    if (idx < 0 || idx >= (int)GameFactory::gameNames().size())
        idx = 0;
    selected = idx;
    saveSettings();
}

int GameManager::getSelected() const { return selected; }

std::unique_ptr<IGame> GameManager::createSelectedGame() const
{
    return GameFactory::create(static_cast<GameFactory::GameId>(selected));
}

void GameManager::loadSettings()
{
    std::ifstream ifs(SETTINGS_FILE);
    if (!(ifs >> selected))
        selected = 0;
}

void GameManager::saveSettings() const
{
    std::ofstream ofs(SETTINGS_FILE, std::ios::trunc);
    ofs << "Game choosing: " << selected;
}