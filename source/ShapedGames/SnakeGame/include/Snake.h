#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Food.h"

namespace Snake
{
    struct Segment
    {
        sf::RectangleShape shape;
        Segment(sf::Vector2f pos = {0, 0}, sf::Vector2f size = {CELL, CELL}, sf::Color c = sf::Color::Green)
        {
            shape.setSize(size);
            shape.setPosition(pos);
            shape.setFillColor(c);
        }
    };

    class Snake
    {
    public:
        Snake();
        void init(sf::Vector2f headPos, sf::Color col, sf::Vector2f dir);
        void update();
        void setDirection(sf::Vector2f d);
        sf::Vector2f getDirection() const;
        sf::Vector2f headPos() const;
        void grow();
        void draw(sf::RenderTarget &rt) const;
        bool checkSelfCollision() const;
        const std::vector<Segment> &body() const { return m_body; }

    private:
        std::vector<Segment> m_body;
        sf::Vector2f m_dir{0, 0};
        std::vector<sf::Vector2f> m_history;
        int m_delay = 1;
    };

}