#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class IGame
{
public:
    virtual ~IGame() = default;
    virtual void init(sf::RenderWindow &window) = 0;
    virtual void run(sf::RenderWindow &window) = 0;
    virtual void cleanup() = 0;
    virtual std::string name() const = 0;
};
