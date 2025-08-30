#include "../include/Pipe.h"

namespace Flappy
{
    /**
     * @class Pipe
     * @brief Represents a pair of pipes in the Flappy Bird game.
     *
     * Each Pipe object consists of an upper and lower pipe with a gap
     * in between. Handles movement and checks if the pipe is off-screen.
     */
    
    /**
     * @brief Constructor. Sets up a pipe pair with given position and gap.
     * 
     * @param x The x-coordinate of the pipe pair.
     * @param gapY The y-coordinate of the top of the gap.
     * @param gapHeight The height of the gap between upper and lower pipes.
     * @param tex Reference to the TextureManager to get pipe textures.
     * @param windowHeight The height of the game window (used for positioning).
     */
    Pipe::Pipe(float x, float gapY, float gapHeight, const TextureManager &tex, float windowHeight)
        : m_scored(false), m_upper(tex.getPipe()), m_lower(tex.getPipe()) // Init pipes
    {
        // Setup upper pipe
        m_upper.setTexture(tex.getPipe()); // Set pipe texture
        m_upper.setScale({1.8f, -2.6f});   // Scale and flip for top
        m_upper.setPosition({x, gapY});    // Put at given x and gap y

        // Setup lower pipe
        m_lower.setTexture(tex.getPipe());          // Set pipe texture
        m_lower.setScale({1.8f, 2.6f});             // Scale for bottom
        m_lower.setPosition({x, gapY + gapHeight}); // Put below gap
    }

    /**
     * @brief Moves both pipes to the left.
     *
     * This simulates the pipes scrolling across the screen.
     *
     * @param speed The speed at which the pipes move left.
     */
    void Pipe::update(float speed)
    {
        m_upper.move({-speed, 0.f}); // Move upper pipe
        m_lower.move({-speed, 0.f}); // Move lower pipe
    }

    /**
     * @brief Checks if the pipe pair has moved off the left side of the screen.
     *
     * @return True if the upper pipe is completely off-screen, false otherwise.
     */
    bool Pipe::isOffScreen() const
    {
        return m_upper.getPosition().x + m_upper.getGlobalBounds().size.x < 0.f;
    }
}
