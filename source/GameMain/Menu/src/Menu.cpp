
/**
 * @file Menu.cpp
 * @brief Implements the Menu class methods for main and settings menu.
 */

#include "../include/Menu.h"
#include "../../Core/include/GameManager.h"
#include "../include/FadeEffect.h"
#include <iostream>

/**
 * @brief Constructs a Menu object and loads resources.
 * @param window Reference to the SFML render window.
 */
Menu::Menu(sf::RenderWindow &window)
    : m_window(window), m_selectedIndex(0), m_background(window, 150), m_titleSprite(m_titleTexture), m_clickSound(m_clickBuffer)
{
    // ...existing code...
}

/**
 * @brief Runs the main menu loop, handles input and transitions.
 * @return Selected menu option index.
 */
int Menu::run()
{
    // ...existing code...
}

/**
 * @brief Runs the settings menu for game selection.
 * @return Selected settings option index.
 */
int Menu::runSettings()
{
    // ...existing code...
}

/**
 * @brief Moves the selection up in the menu.
 */
void Menu::moveUp()
{
    // ...existing code...
}

/**
 * @brief Moves the selection down in the menu.
 */
void Menu::moveDown()
{
    // ...existing code...
}
