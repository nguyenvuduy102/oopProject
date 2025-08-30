// SFML Graphics
#include <SFML/Graphics.hpp>
// Game Menu
#include "GameMain/Menu/include/Menu.h"
// Game Factory layout
#include "GameMain/Core/include/GameFactory.h"
// Game Core
#include "GameMain/Core/include/GameManager.h"

int main()
{
    // Create Window with 800px width and 600px height 
    sf::RenderWindow window(sf::VideoMode({1920,1080}), "Retro Arcade", sf::Style::Titlebar | sf::Style::Close , sf::State::Fullscreen);
    // Set Max Fps to 60
    window.setFramerateLimit(60);

    Menu menu(window);
    // Main Game Loop
    while (window.isOpen())
    {
        // Run the menu and capture the user's menu selection
        int choice = menu.run();
        // Handle menu choices
        if (choice == 0) // Play
        {
            auto game = GameFactory::create(
                static_cast<GameFactory::GameId>(GameManager::instance().getSelected()));
            if (game)
            {
                // Game Components Init
                game->init(window);
                // Running Game
                game->run(window);
                // Clean up thing in game
                game->cleanup();
            }
        }
        else if (choice == 2) // Exit Game
        {
            // Close the window to exit
            window.close();
        }
    }

    return 0;
}
