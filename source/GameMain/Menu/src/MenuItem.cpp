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

    m_background.setOutlineThickness(2.f);
    m_background.setOutlineColor(sf::Color::White);
    sf::FloatRect bounds = m_text.getLocalBounds(); // Grab text’s bounding box to figure out how to center it
    m_text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                      bounds.position.y + bounds.size.y / 2.f}); // Set text origin to its center
    m_text.setPosition(m_background.getPosition());              // Make text sit right on top of background’s center
}

// Change how menu item look when selected or not
void MenuItem::setSelected(bool selected)
{
    m_isSelected = selected;
    m_targetScale = selected ? 1.05f : 1.0f;

    if (!selected)
    {
        m_background.setFillColor(sf::Color(0, 0, 0, 150));
    }
    else
    {
        m_background.setFillColor(sf::Color(255, 255, 255, 180));
    }
}

// Update the menu item’s animation
void MenuItem::update(float dt)
{
    m_currentScale += (m_targetScale - m_currentScale) * dt * m_lerpSpeed;
    m_background.setScale({m_currentScale, m_currentScale});
}

// Draw the menu item onto the window
//  window of SFML
void MenuItem::draw(sf::RenderWindow &window)
{
    window.draw(m_background); // Draw background rectangle
    window.draw(m_text);       // Draw text on top
}