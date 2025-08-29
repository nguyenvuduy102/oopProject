#include "../include/Bird.h"

namespace Flappy
{
    Bird::Bird(const TextureManager &tex)
        : m_textures(tex), m_velocity(0.f), m_frame(0), m_sprite(tex.getBird(0))
    {
        m_sprite.setTexture(m_textures.getBird(0));
        m_sprite.setScale({1.5f, 1.5f});
        m_sprite.setPosition({200.f, 300.f});
    }

    void Bird::reset(const sf::Vector2u &windowSize)
    {
        m_velocity = 0.f;
        m_frame = 0;
        m_sprite.setTexture(m_textures.getBird(0));
        m_sprite.setPosition({windowSize.x * 0.3f, windowSize.y * 0.5f});
    }

    void Bird::flap(float impulse)
    {
        m_velocity = impulse;
    }

    void Bird::update(float gravity, int frames, bool animate, bool physics)
    {
        if (animate && (frames % 6 == 0))
        {
            m_frame = (m_frame + 1) % 3;
            m_sprite.setTexture(m_textures.getBird(m_frame));
        }

        if (physics)
        {
            m_sprite.move({0.f, m_velocity});
            m_velocity += gravity;
            if (m_sprite.getPosition().y < 0.f)
            {
                m_sprite.setPosition({m_sprite.getPosition().x, 0.f});
                m_velocity = 0.f;
            }
        }
    }
}
