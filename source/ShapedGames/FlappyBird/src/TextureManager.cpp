#include "../include/TextureManager.h"
#include <stdexcept>

namespace Flappy
{
    TextureManager::TextureManager() {}

    void TextureManager::load()
    {
        if (!m_bird[0].loadFromFile("assets/images/flappy1.png"))
            throw std::runtime_error("failed to load flappy1.png");
        if (!m_bird[1].loadFromFile("assets/images/flappy2.png"))
            throw std::runtime_error("failed to load flappy2.png");
        if (!m_bird[2].loadFromFile("assets/images/flappy3.png"))
            throw std::runtime_error("failed to load flappy3.png");
        if (!m_pipe.loadFromFile("assets/images/pipe.png"))
            throw std::runtime_error("failed to load pipe.png");
        if (!m_background.loadFromFile("assets/images/background.png"))
            throw std::runtime_error("failed to load background.png");
        if (!m_gameover.loadFromFile("assets/images/gameover.png"))
            throw std::runtime_error("failed to load gameover.png");
    }
}
