#include "../include/GameManager.h"
#include <fstream>

static const char *SETTINGS_FILE = "settings.txt"; // Path to settings file

// Get single instance of GameManager (singleton pattern)
GameManager &GameManager::instance()
{
    static GameManager inst; // Create one instance, keep it forever
    return inst;             // Return that instance
}

// Constructor, load settings when created
GameManager::GameManager() { loadSettings(); } // Just call loadSettings to init

// Set which game is selected
void GameManager::setSelected(int idx)
{
    // Make sure index is valid, else set to 0
    if (idx < 0 || idx >= (int)GameFactory::gameNames().size())
        idx = 0;
    selected = idx; // Store the selected game index
    saveSettings(); // Save choice to file
}

// Get the selected game’s index
int GameManager::getSelected() const { return selected; } // Just return the index

// Create the selected game
std::unique_ptr<IGame> GameManager::createSelectedGame() const
{
    // Make game based on selected index
    return GameFactory::create(static_cast<GameFactory::GameId>(selected));
}

// Load settings from file
void GameManager::loadSettings()
{
    std::ifstream ifs(SETTINGS_FILE); // Open settings file
    if (!(ifs >> selected))           // If can’t read index
        selected = 0;                 // Default to 0
}

// Save settings to file
void GameManager::saveSettings() const
{
    std::ofstream ofs(SETTINGS_FILE, std::ios::trunc); // Open file
    ofs << "Game choosing: " << selected;              // Write selected game
}