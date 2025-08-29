#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SnowBackground.h"
#include "MenuItem.h"
#include <vector>
#include <string>

class Menu
{
public:
    Menu(sf::RenderWindow &window);

    int run();         // chạy Main Menu
    int runSettings(); // chạy menu chọn game

private:
    void moveUp();
    void moveDown();

    sf::RenderWindow &m_window;
    sf::Font m_font;
    std::vector<MenuItem> m_options; // Play / Settings / Exit
    int m_selectedIndex;
    sf::Music m_music;
    sf::SoundBuffer m_clickBuffer;
    sf::Sound m_clickSound;

    // ⬅ giữ lại nền làm member
    SnowBackground m_background;
    sf::Clock m_clock;
    sf::Texture m_titleTexture;
    sf::Sprite m_titleSprite;
};

#endif
