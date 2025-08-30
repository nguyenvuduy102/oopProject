#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace Flappy
{
    // Pipe class, handle pipe pair (upper and lower)
    class Pipe
    {
    public:
        // Constructor, set up pipe at x, gap position, and gap size
        Pipe(float x, float gapY, float gapHeight, const TextureManager &tex, float windowHeight);
        // Move pipe based on speed
        void update(float speed);
        // Get upper pipe sprite
        const sf::Sprite &upper() const { return m_upper; }
        // Get lower pipe sprite
        const sf::Sprite &lower() const { return m_lower; }
        // Check if pipe off screen
        bool isOffScreen() const;
        // Check if pipe already scored
        bool hasScored() const { return m_scored; }
        // Mark pipe as scored
        void setScored() { m_scored = true; }

    private:
        sf::Sprite m_upper; // Upper pipe sprite
        sf::Sprite m_lower; // Lower pipe sprite
        bool m_scored;      // Track if scored already
    };
}