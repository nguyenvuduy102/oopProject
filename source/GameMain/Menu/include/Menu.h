#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "MenuItem.h"
#include <vector>
#include <string>

class Menu
{
public:
    Menu(sf::RenderWindow &window);

    int run();
    int runSettings();

private:
    void moveUp();
    void moveDown();

    sf::RenderWindow &m_window;
    sf::Font m_font;
    std::vector<MenuItem> m_options;
    int m_selectedIndex;

    sf::Clock m_clock;
    sf::Texture m_titleTexture;
    sf::Sprite m_titleSprite;
};

#endif
