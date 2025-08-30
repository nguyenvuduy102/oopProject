#ifndef MENU_H // Guard to prevent multiple includes
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SnowBackground.h"
#include "MenuItem.h"
#include <vector>
#include <string>

// Menu class, handle main menu and settings
class Menu
{
public:
    // Constructor, set up menu with window
    Menu(sf::RenderWindow &window);

    // Run main menu, return user choice
    int run();
    // Run settings menu for picking game
    int runSettings();
    int runCredits(); // hiển thị credits
    int runHelp();    // hiển thị hướng dẫn

private:
    // Move selection up in menu
    void moveUp();
    // Move selection down in menu
    void moveDown();

    sf::RenderWindow &m_window;      // Ref to SFML window
    sf::Font m_font;                 // Font for menu text
    std::vector<MenuItem> m_options; // List of menu items (Play, Settings, Exit)
    int m_selectedIndex;             // Track which item picked
    sf::Music m_music;               // Background music
    sf::SoundBuffer m_clickBuffer;   // Buffer for click sound
    sf::Sound m_clickSound;          // Click sound effect
    sf::SoundBuffer m_slideBuffer;   // Slide sound effect
    sf::Sound m_slideSound;          // Buffer for slide sound

    // Keep background as member
    SnowBackground m_background; // Snowy background effect
    sf::Clock m_clock;           // Clock for timing
    sf::Texture m_titleTexture;  // Texture for title image
    sf::Sprite m_titleSprite;    // Sprite for title image
};

#endif