#include "../include/TextureManager.h"
#include <stdexcept>

namespace Flappy
{
    // Constructor, do nothing yet
    TextureManager::TextureManager() {}

    // Load all textures
    void TextureManager::load()
    {
        // Try load bird textures, crash if fail
        if (!m_bird[0].loadFromFile("../source/assets/images/flappy1.png"))
            throw std::runtime_error("failed to load flappy1.png");
        if (!m_bird[1].loadFromFile("../source/assets/images/flappy2.png"))
            throw std::runtime_error("failed to load flappy2.png");
        if (!m_bird[2].loadFromFile("../source/assets/images/flappy3.png"))
            throw std::runtime_error("failed to load flappy3.png");
        // Load pipe texture
        if (!m_pipe.loadFromFile("../source/assets/images/pipe.png"))
            throw std::runtime_error("failed to load pipe.png");
        // Load background texture
        if (!m_background.loadFromFile("../source/assets/images/background.png"))
            throw std::runtime_error("failed to load background.png");
        // Load game over texture
        if (!m_gameover.loadFromFile("../source/assets/images/gameover.png"))
            throw std::runtime_error("failed to load gameover.png");
    }
}