#include "../include/Bird.h"

namespace Flappy
{
    // Constructor, set up bird with texture
    Bird::Bird(const TextureManager &tex)
        : m_textures(tex), m_velocity(0.f), m_frame(0), m_sprite(tex.getBird(0))
    {
        m_sprite.setTexture(m_textures.getBird(0)); // Set first bird texture
        m_sprite.setScale({1.5f, 1.5f});            // Make bird bigger
        m_sprite.setPosition({200.f, 300.f});       // Start position
    }

    // Reset bird to start position
    void Bird::reset(const sf::Vector2u &windowSize)
    {
        m_velocity = 0.f;                                                 // Reset speed
        m_frame = 0;                                                      // Reset animation
        m_sprite.setTexture(m_textures.getBird(0));                       // Set first texture
        m_sprite.setPosition({windowSize.x * 0.3f, windowSize.y * 0.5f}); // Center in window
    }

    // Make bird jump
    void Bird::flap(float impulse)
    {
        m_velocity = impulse; // Set upward speed
    }

    // Update bird position and animation
    void Bird::update(float gravity, int frames, bool animate, bool physics)
    {
        // Update animation if needed
        if (animate && (frames % 6 == 0))
        {
            m_frame = (m_frame + 1) % 3;                      // Cycle through 3 frames
            m_sprite.setTexture(m_textures.getBird(m_frame)); // Set new texture
        }

        // Update position if physics on
        if (physics)
        {
            m_sprite.move({0.f, m_velocity});   // Move by velocity
            m_velocity += gravity;              // Apply gravity
            if (m_sprite.getPosition().y < 0.f) // If hit top
            {
                m_sprite.setPosition({m_sprite.getPosition().x, 0.f}); // Stay at top
                m_velocity = 0.f;                                      // Stop moving up
            }
        }
    }
}