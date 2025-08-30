
/**
 * @file GameManager.h
 * @brief Declares the GameManager class for managing game selection and settings.
 */
#pragma once
#include <memory>
#include "IGame.h"
#include "GameFactory.h"

/**
 * @class GameManager
 * @brief Singleton class for managing game selection and settings.
 */
class GameManager
{
public:
    /**
     * @brief Gets the singleton instance of GameManager.
     * @return Reference to the GameManager instance.
     */
    static GameManager &instance();

    /**
     * @brief Sets the selected game index.
     * @param idx Index of the selected game.
     */
    void setSelected(int idx);

    /**
     * @brief Gets the selected game index.
     * @return Index of the selected game.
     */
    int getSelected() const;

    /**
     * @brief Creates an instance of the selected game.
     * @return Unique pointer to IGame instance.
     */
    std::unique_ptr<IGame> createSelectedGame() const;

    /**
     * @brief Loads game settings from storage.
     */
    void loadSettings();

    /**
     * @brief Saves game settings to storage.
     */
    void saveSettings() const;

private:
    /**
     * @brief Constructs a GameManager object.
     */
    GameManager();

    int selected = 0; /**< Index of the selected game. */
};
