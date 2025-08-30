/**
 * @file MenuItem.cpp
 * @brief Implements the MenuItem class methods.
 */

#include "../include/Menu.h"

/**
 * @brief Constructs a MenuItem object.
 * @param text Display text for the menu item.
 * @param font Font used for the text.
 * @param size Font size.
 * @param pos Position of the menu item.
 */
MenuItem::MenuItem(const std::string &text, const sf::Font &font, unsigned int size, sf::Vector2f pos)
    : m_text(font, text, size) // <-- initialize here
{
    m_text.setFillColor(sf::Color::White);

    // setup background
    m_background.setSize({200.f, 50.f});
    m_background.setFillColor(sf::Color(0, 0, 0, 150));
    m_background.setOrigin(m_background.getSize() / 2.f);

    // center text
    m_background.setPosition(pos);
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                      bounds.position.y + bounds.size.y / 2.f});
    m_text.setPosition(m_background.getPosition());
}

/**
 * @brief Sets whether the item is selected.
 * @param selected True if selected, false otherwise.
 */
void MenuItem::setSelected(bool selected)
{
    m_isSelected = selected;
    if (!selected)
    {
        m_background.setScale({1.f, 1.f});
        m_background.setFillColor(sf::Color(0, 0, 0, 150));
    }
}

/**
 * @brief Updates the menu item (e.g., animation).
 * @param dt Delta time in seconds.
 */
void MenuItem::update(float dt)
{
    if (m_isSelected)
    {
        m_animationTime += dt * 3.f; // tốc độ pulse
        float scale = 1.f + 0.05f * std::sin(m_animationTime * 3.14f);
        m_background.setScale({scale, scale});

        // đổi màu nền thành trắng đục
        m_background.setFillColor(sf::Color(255, 255, 255, 180));
    }
}

/**
 * @brief Draws the menu item to the window.
 * @param window Reference to the SFML render window.
 */
void MenuItem::draw(sf::RenderWindow &window)
{
    window.draw(m_background);
    window.draw(m_text);
}
