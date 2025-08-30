#pragma once // Stop multiple includes
#include <memory>
#include "IGame.h"
#include "GameFactory.h"

// GameManager class, handle game selection and settings
class GameManager
{
public:
    // Get single instance (singleton)
    static GameManager &instance();
    // Set which game is picked
    void setSelected(int idx);
    // Get selected game index
    int getSelected() const;
    // Make the selected game
    std::unique_ptr<IGame> createSelectedGame() const;
    // Load settings from file
    void loadSettings();
    // Save settings to file
    void saveSettings() const;

private:
    // Constructor, private for singleton
    GameManager();
    int selected = 0; // Store selected game index
};