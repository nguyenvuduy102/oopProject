#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>

namespace Tetris
{
    /**
     * @brief Predefined color constants used in the Tetris game.
     */
    extern const sf::Color darkGrey;  ///< Dark grey color.
    extern const sf::Color green;     ///< Green color.
    extern const sf::Color red;       ///< Red color.
    extern const sf::Color orange;    ///< Orange color.
    extern const sf::Color yellow;    ///< Yellow color.
    extern const sf::Color purple;    ///< Purple color.
    extern const sf::Color cyan;      ///< Cyan color.
    extern const sf::Color blue;      ///< Blue color.
    extern const sf::Color lightBlue; ///< Light blue color.
    extern const sf::Color darkBlue;  ///< Dark blue color.
    extern const sf::Color lightGray; ///< Light gray color.
    extern const sf::Color darkLight; ///< Dark light color.

    /**
     * @brief Gets the list of colors used for Tetris cells.
     * @return A vector of sf::Color objects for different block types.
     */
    std::vector<sf::Color> GetCellColors();
}