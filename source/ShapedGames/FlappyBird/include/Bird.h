#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace Flappy
{
    // Bird class, handle bird movement and animation
    class Bird
    {
    public:
        // Constructor, set up bird with textures
        Bird(const TextureManager &tex);
        // Reset bird position and state
        void reset(const sf::Vector2u &windowSize);
        // Make bird jump with impulse
        void flap(float impulse);
        // Update bird position and animation
        void update(float gravity, int frames, bool animate, bool physics);
        // Get bird sprite for rendering
        sf::Sprite &sprite() { return m_sprite; }
        // Get bird sprite for reading
        const sf::Sprite &sprite() const { return m_sprite; }
        // Get bird’s hitbox
        sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }
        // Get bird’s position
        sf::Vector2f getPosition() const { return m_sprite.getPosition(); }

    private:
        const TextureManager &m_textures; // Texture manager ref
        sf::Sprite m_sprite;              // Bird sprite
        float m_velocity;                 // Bird’s vertical speed
        int m_frame;                      // Current animation frame
    };
}