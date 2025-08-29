#pragma once
#include <SFML/Graphics.hpp>
#include <array>

namespace Flappy
{
    class TextureManager
    {
    public:
        TextureManager();
        void load();
        const sf::Texture &getBird(int frame) const { return m_bird[frame]; }
        const sf::Texture &getPipe() const { return m_pipe; }
        const sf::Texture &getBackground() const { return m_background; }
        const sf::Texture &getGameover() const { return m_gameover; }

    private:
        std::array<sf::Texture, 3> m_bird;
        sf::Texture m_pipe;
        sf::Texture m_background;
        sf::Texture m_gameover;
    };
}
