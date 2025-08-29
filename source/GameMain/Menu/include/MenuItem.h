#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class MenuItem
{
public:
    MenuItem(const std::string &text, const sf::Font &font, unsigned int size, sf::Vector2f pos);

    void setSelected(bool selected);
    void update(float dt);
    void draw(sf::RenderWindow &window);

private:
    sf::Text m_text;
    sf::RectangleShape m_background;

    bool m_isSelected = false;
    float m_currentScale = 1.f;
    float m_targetScale = 1.f;
    float m_lerpSpeed = 10.f;
    float m_animationTime = 0.f; // để pulse
};

#endif
