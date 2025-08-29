#include "../include/Menu.h"
#include "../../Core/include/GameManager.h"
#include "../include/FadeEffect.h"
#include <iostream>

// Constructor for Menu class, initializes menu elements
Menu::Menu(sf::RenderWindow &window)
    : m_window(window), m_selectedIndex(0), m_background(window, 150), m_titleSprite(m_titleTexture), m_clickSound(m_clickBuffer)
{
    // Load font for menu text
    if (!m_font.openFromFile("../source/assets/fonts/Montserrat-Regular.ttf"))
    {
        std::cerr << "Error: Cannot load font!\n";
    }

    // Load background music
    if (!m_music.openFromFile("../source/assets/sounds/Presstart.wav"))
    {
        std::cerr << "Error: Cannot load music!\n";
    }
    else
    {
        // Configure and play music
        m_music.setLooping(true);
        m_music.setVolume(50.f);
        m_music.play();
    }

    // Load click sound effect
    if (!m_clickBuffer.loadFromFile("../source/assets/sounds/MinecraftSounds.wav"))
    {
        std::cerr << "Error: Cannot load click sound!\n";
    }
    else
    {
        // Configure click sound
        m_clickSound.setBuffer(m_clickBuffer);
        m_clickSound.setVolume(100.f);
        m_clickSound.setPitch(2.0f);
    }

    // Load title image
    if (!m_titleTexture.loadFromFile("../source/assets/images/GameIcon.png"))
    {
        std::cerr << "Error: Cannot load title image!\n";
    }
    else
    {
        // Set up title sprite and center it
        m_titleSprite = sf::Sprite(m_titleTexture);
        sf::Vector2u winSize = m_window.getSize();
        sf::FloatRect bounds = m_titleSprite.getLocalBounds();
        m_titleSprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        m_titleSprite.setPosition({winSize.x / 2.f, 150.f});
    }

    // Initialize menu items (Play, Settings, Exit)
    std::vector<std::string> labels = {"Play", "Game", "Exit"};
    for (size_t i = 0; i < labels.size(); i++)
    {
        MenuItem item(labels[i], m_font, 20, {400.f, 300.f + i * 60.f});
        m_options.push_back(item);
    }
}

// Main menu loop, handles user input and rendering
int Menu::run()
{
    // Ensure background music is playing
    if (m_music.getStatus() != sf::Music::Status::Playing)
    {
        m_music.play();
    }
    FadeEffect fade(m_window.getSize()); // Initialize fade effect overlay
    bool startAction = false;
    int actionIndex = -1;

    // Menu loop
    while (m_window.isOpen())
    {
        // Update delta time for animations
        float dt = m_clock.restart().asSeconds();

        // Handle events
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return 2; // Return exit code
            }
            if (auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (fade.isFading())
                    continue; // Ignore input during fade

                // Navigate menu with keyboard
                if (keyEvent->scancode == sf::Keyboard::Scan::Up || keyEvent->scancode == sf::Keyboard::Scan::W)
                    moveUp();
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down || keyEvent->scancode == sf::Keyboard::Scan::S)
                    moveDown();
                else if (keyEvent->scancode == sf::Keyboard::Scan::Enter)
                {
                    // Play click sound and start fade effect
                    if (m_clickSound.getStatus() != sf::Sound::Status::Playing)
                        m_clickSound.play();
                    fade.startFadeIn(0.5f);
                    startAction = true;
                    actionIndex = m_selectedIndex;
                }
            }
        }

        // Update and render background (snow + gradient)
        m_background.update(dt);
        m_window.draw(m_titleSprite);

        // Update and draw menu items
        for (size_t i = 0; i < m_options.size(); i++)
        {
            m_options[i].setSelected(i == m_selectedIndex);
            m_options[i].update(dt);
            m_options[i].draw(m_window);
        }

        // Update and draw fade effect
        fade.update(dt);
        fade.draw(m_window);
        m_window.display();

        // Handle menu actions after fade completes
        if (startAction && !fade.isFading())
        {
            if (actionIndex == 0)
            {
                m_music.stop();
                return 0; // Return code for "Play"
            }
            else if (actionIndex == 1)
            {
                // Open settings menu and update selected game
                int chosen = runSettings();
                if (chosen >= 0)
                    GameManager::instance().setSelected(chosen);
                m_selectedIndex = 0;
            }
            else if (actionIndex == 2)
            {
                return 2; // Return code for "Exit"
            }

            // Start fade out to return to menu
            fade.startFadeOut(1.0f);
            startAction = false;
        }
    }
    return 2; // Default exit code
}

// Settings menu loop for selecting games
int Menu::runSettings()
{
    // List of available games and "Back" option
    std::vector<std::string> games = {"Tetris", "Snake", "Pong", "Flappy Bird", "Back"};
    int selected = 0;

    // Initialize settings menu items
    std::vector<MenuItem> gameOptions;
    for (size_t i = 0; i < games.size(); i++)
    {
        MenuItem item(games[i], m_font, 20, {400.f, 300.f + i * 60.f});
        gameOptions.push_back(item);
    }

    // Settings menu loop
    while (m_window.isOpen())
    {
        float dt = m_clock.restart().asSeconds();

        // Handle events
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return -1; // Return on window close
            }
            if (auto keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                // Navigate settings menu
                if (keyEvent->scancode == sf::Keyboard::Scan::Up || keyEvent->scancode == sf::Keyboard::Scan::W)
                    selected = (selected > 0) ? selected - 1 : (int)gameOptions.size() - 1;
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down || keyEvent->scancode == sf::Keyboard::Scan::S)
                    selected = (selected < (int)gameOptions.size() - 1) ? selected + 1 : 0;
                else if (keyEvent->scancode == sf::Keyboard::Scan::Enter)
                {
                    // Play click sound
                    if (m_clickSound.getStatus() != sf::Sound::Status::Playing)
                        m_clickSound.play();
                    if (selected == (int)gameOptions.size() - 1)
                        return -1;   // Return for "Back"
                    return selected; // Return selected game index
                }
            }
        }

        // Update and render background and title
        m_background.update(dt);
        m_window.draw(m_titleSprite);

        // Update and draw settings menu items
        for (size_t i = 0; i < gameOptions.size(); i++)
        {
            gameOptions[i].setSelected(i == selected);
            gameOptions[i].update(dt);
            gameOptions[i].draw(m_window);
        }

        m_window.display();
    }
    return -1; // Default return for settings menu
}

// Move selection up in the menu
void Menu::moveUp()
{
    if (m_selectedIndex > 0)
        m_selectedIndex--;
    else
        m_selectedIndex = m_options.size() - 1;
}

// Move selection down in the menu
void Menu::moveDown()
{
    if (m_selectedIndex < (int)m_options.size() - 1)
        m_selectedIndex++;
    else
        m_selectedIndex = 0;
}