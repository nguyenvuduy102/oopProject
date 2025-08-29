#include "../include/colors.h"

namespace Tetris
{
    const sf::Color darkGrey(26, 31, 40, 255);
    const sf::Color green(47, 230, 23, 255);
    const sf::Color red(232, 18, 18, 255);
    const sf::Color orange(226, 116, 17, 255);
    const sf::Color yellow(237, 234, 4, 255);
    const sf::Color purple(166, 0, 247, 255);
    const sf::Color cyan(21, 204, 209, 255);
    const sf::Color blue(13, 64, 216, 255);
    const sf::Color lightBlue(59, 85, 162, 255);
    const sf::Color darkBlue(44, 44, 127, 255);
    const sf::Color lightGray(150, 150, 150, 255);
    const sf::Color darkLight(200, 200, 200, 255);

    std::vector<sf::Color> GetCellColors()
    {
        return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
    }
}