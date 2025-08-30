/**
 * @file Menu.h
 * @brief Declares the Menu class for the main and settings menu.
 */
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SnowBackground.h"
#include "MenuItem.h"
#include <vector>
#include <string>

/**
 * @class Menu
 * @brief Handles the main menu and settings menu.
 */
class Menu
{
public:
    /**
     * @brief Constructs a Menu object.
     * @param window Reference to the SFML render window.
     */
    Menu(sf::RenderWindow &window);

    /**
     * @brief Runs the main menu.
     * @return Selected menu option index.
     */
    int run();

    /**
     * @brief Runs the settings menu for game selection.
     * @return Selected settings option index.
     */
    int runSettings();
    /**
     * @brief Runs the credits for game selection.
     * @return Selected credits.
     */
    int runCredits();
    /**
     * @brief Runs the help menu for game selection.
     * @return Selected help option index
     */
    int runHelp();

private:
    /**
     * @brief Moves the selection up in the menu.
     */
    void moveUp();

    /**
     * @brief Moves the selection down in the menu.
     */
    void moveDown();

    sf::RenderWindow &m_window;      /**< Reference to the render window. */
    sf::Font m_font;                 /**< Font used for menu text. */
    std::vector<MenuItem> m_options; /**< Menu options (Play / Settings / Exit). */
    int m_selectedIndex;             /**< Index of the selected menu item. */
    sf::Music m_music;               /**< Background music. */
    sf::SoundBuffer m_clickBuffer;   /**< Sound buffer for click sound. */
    sf::Sound m_clickSound;          /**< Click sound effect. */
    sf::SoundBuffer m_slideBuffer;   /**< Sound buffer for slide sound. */
    sf::Sound m_slideSound;          /**< Slide sound effect */
    SnowBackground m_background;     /**< Snow background effect. */
    sf::Clock m_clock;               /**< Clock for timing. */
    sf::Texture m_titleTexture;      /**< Texture for the menu title. */
    sf::Sprite m_titleSprite;        /**< Sprite for the menu title. */
};

#endif
