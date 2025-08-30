#include "../include/Bird.h"

namespace Flappy
{
    /**
     * @brief Constructor. Initializes the bird with the first texture, scale, and start position.
     * @param tex Reference to the TextureManager for loading bird textures.
     */
    Bird::Bird(const TextureManager &tex)
        : m_textures(tex), m_velocity(0.f), m_frame(0), m_sprite(tex.getBird(0))
    {
        m_sprite.setTexture(m_textures.getBird(0));  // Set the first bird texture
        m_sprite.setScale({1.5f, 1.5f});             // Scale the bird up
        m_sprite.setPosition({200.f, 300.f});        // Initial start position
    }

    /**
     * @brief Reset the bird to its initial state and position.
     * @param windowSize The size of the game window.
     */
    void Bird::reset(const sf::Vector2u &windowSize)
    {
        m_velocity = 0.f;                                                  // Reset velocity
        m_frame = 0;                                                       // Reset animation frame
        m_sprite.setTexture(m_textures.getBird(0));                        // Reset to first texture
        m_sprite.setPosition({windowSize.x * 0.3f, windowSize.y * 0.5f});  // Place near window center
    }

    /**
     * @brief Make the bird flap (jump upwards).
     * @param impulse The upward velocity applied to the bird.
     */
    void Bird::flap(float impulse)
    {
        m_velocity = impulse;
    }

    /**
     * @brief Update the bird’s position, animation, and physics.
     * @param gravity Downward force applied to the bird.
     * @param frames Current frame count, used for animation timing.
     * @param animate Whether the bird’s animation should be updated.
     * @param physics Whether physics (movement & gravity) should be applied.
     */
    void Bird::update(float gravity, int frames, bool animate, bool physics)
    {
        // Update animation every 6 frames
        if (animate && (frames % 6 == 0))
        {
            m_frame = (m_frame + 1) % 3;                       // Cycle between 3 frames
            m_sprite.setTexture(m_textures.getBird(m_frame));  // Apply new frame texture
        }

        // Apply movement and gravity if physics is enabled
        if (physics)
        {
            m_sprite.move({0.f, m_velocity});  // Move vertically based on velocity
            m_velocity += gravity;             // Apply gravity to velocity

            // Prevent the bird from going above the screen
            if (m_sprite.getPosition().y < 0.f)
            {
                m_sprite.setPosition({m_sprite.getPosition().x, 0.f});  // Lock at top
                m_velocity = 0.f;                                      // Stop upward motion
            }
        }
    }
}
