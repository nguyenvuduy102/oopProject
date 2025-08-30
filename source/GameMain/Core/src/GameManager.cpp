
/**
 * @file GameManager.cpp
 * @brief Implements the GameManager class methods.
 */

#include "../include/GameManager.h"
#include <fstream>

/// Path to the settings file.
static const char *SETTINGS_FILE = "settings.txt";

/**
 * @brief Gets the singleton instance of GameManager.
 * @return Reference to the GameManager instance.
 */
GameManager &GameManager::instance()
{
    static GameManager inst;
    return inst;
}

/**
 * @brief Constructs a GameManager object and loads settings.
 */
GameManager::GameManager() { loadSettings(); }

/**
 * @brief Sets the selected game index and saves settings.
 * @param idx Index of the selected game.
 */
void GameManager::setSelected(int idx)
{
    if (idx < 0 || idx >= (int)GameFactory::gameNames().size())
        idx = 0;
    selected = idx;
    saveSettings();
}

/**
 * @brief Gets the selected game index.
 * @return Index of the selected game.
 */
int GameManager::getSelected() const { return selected; }

/**
 * @brief Creates an instance of the selected game.
 * @return Unique pointer to IGame instance.
 */
std::unique_ptr<IGame> GameManager::createSelectedGame() const
{
    return GameFactory::create(static_cast<GameFactory::GameId>(selected));
}

/**
 * @brief Loads game settings from the settings file.
 */
void GameManager::loadSettings()
{
    std::ifstream ifs(SETTINGS_FILE);
    if (!(ifs >> selected))
        selected = 0;
}

/**
 * @brief Saves game settings to the settings file.
 */
void GameManager::saveSettings() const
{
    std::ofstream ofs(SETTINGS_FILE, std::ios::trunc);
    ofs << "Game choosing: " << selected;
}