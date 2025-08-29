#include "../include/Menu.h"

// MenuItem class set up a single menu item like "Play" or "Exit"
// Takes a text string, font, size , and pos
MenuItem::MenuItem(const std::string &text, const sf::Font &font, unsigned int size, sf::Vector2f pos)
    : m_text(font, text, size) // Inits the SFML Text object with given font, text, and size for display
{
    // Make text white so it stand out nice against dark background
    m_text.setFillColor(sf::Color::White);

    // Setup the background rectangle
    m_background.setSize({200.f, 50.f}); // Give it a fixed size
    m_background.setFillColor(sf::Color(0, 0, 0, 150));
    m_background.setOrigin(m_background.getSize() / 2.f); // Set origin to rectangle’s center

    // Gotta center the background and text
    m_background.setPosition(pos);
    sf::FloatRect bounds = m_text.getLocalBounds(); // Grab text’s bounding box to figure out how to center it
    m_text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                      bounds.position.y + bounds.size.y / 2.f}); // Set text origin to its center
    m_text.setPosition(m_background.getPosition());              // Make text sit right on top of background’s center
}

// Change how menu item look when selected or not
void MenuItem::setSelected(bool selected)
{
    m_isSelected = selected; // Store if this item is selected or not in the member variable
    if (!selected)
    {
        m_background.setScale({1.f, 1.f});                  // Set scale back to normal, no zoom or nothing
        m_background.setFillColor(sf::Color(0, 0, 0, 150)); // Go back to default background
    }
}

// Update the menu item’s animation
void MenuItem::update(float dt)
{
    if (m_isSelected) // Only animate if this item is the one selected
    {
        m_animationTime += dt * 3.f;                                   // Bump up animation time
        float scale = 1.f + 0.05f * std::sin(m_animationTime * 3.14f); // Calculate a pulsing effect
        m_background.setScale({scale, scale});                         // Apply that pulsing scale to background

        // Change background to a white color
        m_background.setFillColor(sf::Color(255, 255, 255, 180));
    }
}

// Draw the menu item onto the window
//  window of SFML
void MenuItem::draw(sf::RenderWindow &window)
{
    window.draw(m_background); // Draw background rectangle
    window.draw(m_text);       // Draw text on top
}