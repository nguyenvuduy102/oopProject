#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include <string>

// IGame interface, define what every game gotta do
class IGame
{
public:
    // Virtual destructor for safe cleanup
    virtual ~IGame() = default;
    // Init game with window
    virtual void init(sf::RenderWindow &window) = 0;
    // Run game loop
    virtual void run(sf::RenderWindow &window) = 0;
    // Clean up game stuff
    virtual void cleanup() = 0;
    // Get game name
    virtual std::string name() const = 0;
};