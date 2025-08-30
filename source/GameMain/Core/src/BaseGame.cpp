#include "../include/BaseGame.h"
#include <SFML/Graphics.hpp>
#include <iostream>

static const char *FONT_PATH = "../assets/fonts/monogram.ttf"; // Path to font file

// Constructor for BaseGame, set up game name and background color
BaseGame::BaseGame(const std::string &n, sf::Color bg) : m_name(n), m_bg(bg) {} // Init name and color

// Init game stuff, not much here for base class
void BaseGame::init(sf::RenderWindow &) {}

// Run the game loop, show game name and handle exit
void BaseGame::run(sf::RenderWindow &window)
{
    // Load font for text display
    sf::Font font;
    if (!font.openFromFile(FONT_PATH)) // If font don’t load
    {
        throw std::runtime_error("Không load được font từ " + std::string(FONT_PATH)); // Crash with error
    }

    // Setup text to show game name and exit instruction
    sf::Text text(font, sf::String(m_name + " - Press ESC to return"), 24); // Text with game name
    text.setPosition({40.f, 40.f});                                         // Put text near top-left corner

    // Main game loop
    while (window.isOpen()) // Keep going while window open
    {
        // Handle events
        while (auto evOpt = window.pollEvent()) // Check for events
        {
            const sf::Event &ev = *evOpt;   // Get event
            if (ev.is<sf::Event::Closed>()) // If window closed
            {
                window.close(); // close ưindow
                return;      
            }
            if (auto key = ev.getIf<sf::Event::KeyPressed>()) // If key pressed
            {
                if (key->code == sf::Keyboard::Key::Escape) // If ESC hit
                    return;                                 // Exit game, go back to menu
            }
        }
        window.clear(m_bg); // background color
        window.draw(text);  // Draw  name text
        window.display();   // Show it all on screen
    }
}

// Cleanup game stuff
void BaseGame::cleanup() {}

// Get game name
std::string BaseGame::name() const { return m_name; } // return the name