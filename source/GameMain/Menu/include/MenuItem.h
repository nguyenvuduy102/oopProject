
/**
 * @file MenuItem.h
 * @brief Declares the MenuItem class for menu options.
 */
#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class MenuItem
 * @brief Represents a selectable item in the menu.
 */
class MenuItem
{
public:
    /**
     * @brief Constructs a MenuItem object.
     * @param text Display text for the menu item.
     * @param font Font used for the text.
     * @param size Font size.
     * @param pos Position of the menu item.
     */
    MenuItem(const std::string &text, const sf::Font &font, unsigned int size, sf::Vector2f pos);

    /**
     * @brief Sets whether the item is selected.
     * @param selected True if selected, false otherwise.
     */
    void setSelected(bool selected);

    /**
     * @brief Updates the menu item (e.g., animation).
     * @param dt Delta time in seconds.
     */
    void update(float dt);

    /**
     * @brief Draws the menu item to the window.
     * @param window Reference to the SFML render window.
     */
    void draw(sf::RenderWindow &window);

private:
    sf::Text m_text;                /**< Text displayed for the menu item. */
    sf::RectangleShape m_background;/**< Background shape for the menu item. */

    bool m_isSelected = false;      /**< Whether the item is selected. */
    float m_animationTime = 0.f;    /**< Animation timer for effects (e.g., pulse). */
};

#endif
