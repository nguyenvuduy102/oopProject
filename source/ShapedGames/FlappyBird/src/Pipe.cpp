#include "../include/Pipe.h"

namespace Flappy
{
    Pipe::Pipe(float x, float gapY, float gapHeight, const TextureManager &tex, float windowHeight)
        : m_scored(false), m_upper(tex.getPipe()), m_lower(tex.getPipe())
    {
        m_upper.setTexture(tex.getPipe());
        m_upper.setScale({1.5f, -1.5f});
        m_upper.setPosition({x, gapY});

        m_lower.setTexture(tex.getPipe());
        m_lower.setScale({1.5f, 1.5f});
        m_lower.setPosition({x, gapY + gapHeight});
    }

    void Pipe::update(float speed)
    {
        m_upper.move({-speed, 0.f});
        m_lower.move({-speed, 0.f});
    }

    bool Pipe::isOffScreen() const
    {
        return m_upper.getPosition().x + m_upper.getGlobalBounds().size.x < 0.f;
    }
}
