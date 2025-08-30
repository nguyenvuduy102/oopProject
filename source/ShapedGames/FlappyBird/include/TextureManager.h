#pragma once // Stop multiple includes
#include <SFML/Graphics.hpp>
#include <array>

namespace Flappy
{
    // TextureManager class, load and store textures
    class TextureManager
    {
    public:
        // Constructor, set up texture stuff
        TextureManager();
        // Load all textures
        void load();
        // Get bird texture for frame
        const sf::Texture &getBird(int frame) const { return m_bird[frame]; }
        // Get pipe texture
        const sf::Texture &getPipe() const { return m_pipe; }
        // Get background texture
        const sf::Texture &getBackground() const { return m_background; }
        // Get game over texture
        const sf::Texture &getGameover() const { return m_gameover; }

    private:
        std::array<sf::Texture, 3> m_bird; // Bird animation textures
        sf::Texture m_pipe;                // Pipe texture
        sf::Texture m_background;          // Background texture
        sf::Texture m_gameover;            // Game over texture
    };
}