#include <SFML/Graphics.hpp>
#include "GameMain/Menu/include/Menu.h"
#include "GameMain/Core/include/GameFactory.h"
#include "GameMain/Core/include/GameManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Game Hub - SFML 3.0.0", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Menu menu(window);
    while (window.isOpen())
    {
        int choice = menu.run();

        if (choice == 0) // Play
        {
            auto game = GameFactory::create(
                static_cast<GameFactory::GameId>(GameManager::instance().getSelected()));
            if (game)
            {
                game->init(window);
                game->run(window);
                game->cleanup();
            }
        }
        else if (choice == 2) // Exit
        {
            window.close();
        }
    }

    return 0;
}
