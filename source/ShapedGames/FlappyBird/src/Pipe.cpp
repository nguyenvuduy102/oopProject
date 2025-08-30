#include "../include/Pipe.h"

namespace Flappy
{
    // Constructor, set up pipe pair with position and gap
    Pipe::Pipe(float x, float gapY, float gapHeight, const TextureManager &tex, float windowHeight)
        : m_scored(false), m_upper(tex.getPipe()), m_lower(tex.getPipe()) // Init pipes
    {
        // Setup upper pipe
        m_upper.setTexture(tex.getPipe()); // Set pipe texture
        m_upper.setScale({1.5f, -1.5f});   // Scale and flip for top
        m_upper.setPosition({x, gapY});    // Put at given x and gap y

        // Setup lower pipe
        m_lower.setTexture(tex.getPipe());          // Set pipe texture
        m_lower.setScale({1.5f, 1.5f});             // Scale for bottom
        m_lower.setPosition({x, gapY + gapHeight}); // Put below gap
    }

    // Move pipes left
    void Pipe::update(float speed)
    {
        m_upper.move({-speed, 0.f}); // Move upper pipe
        m_lower.move({-speed, 0.f}); // Move lower pipe
    }

    // Check if pipe off screen
    bool Pipe::isOffScreen() const
    {
        // True if upper pipe fully off left side
        return m_upper.getPosition().x + m_upper.getGlobalBounds().size.x < 0.f;
    }
}