#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace Flappy
{
    class Bird
    {
    public:
        Bird(const TextureManager &tex);
        void reset(const sf::Vector2u &windowSize);
        void flap(float impulse);
        void update(float gravity, int frames, bool animate, bool physics);
        sf::Sprite &sprite() { return m_sprite; }
        const sf::Sprite &sprite() const { return m_sprite; }
        sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }
        sf::Vector2f getPosition() const { return m_sprite.getPosition(); }

    private:
        const TextureManager &m_textures;
        sf::Sprite m_sprite;
        float m_velocity;
        int m_frame;
    };
}
