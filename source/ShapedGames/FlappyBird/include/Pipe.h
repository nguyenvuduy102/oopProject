#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace Flappy
{
    class Pipe
    {
    public:
        Pipe(float x, float gapY, float gapHeight, const TextureManager &tex, float windowHeight);
        void update(float speed);
        const sf::Sprite &upper() const { return m_upper; }
        const sf::Sprite &lower() const { return m_lower; }
        bool isOffScreen() const;
        bool hasScored() const { return m_scored; }
        void setScored() { m_scored = true; }

    private:
        sf::Sprite m_upper;
        sf::Sprite m_lower;
        bool m_scored;
    };
}
