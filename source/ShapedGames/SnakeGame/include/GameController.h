#pragma once
#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include "Snake.h"
#include "Food.h"
#include <optional>

namespace Snake
{
    enum class Mode
    {
        Menu,
        OnePlayer,
        TwoPlayers,
        GameOver
    };

    class GameController
    {
    public:
        GameController(AudioManager &audio);
        void init();
        void update();
        void handleEvent(const std::optional<sf::Event> &ev);

        Mode mode() const { return m_mode; }
        Snake &player1() { return m_p1; }
        const Snake &player1() const { return m_p1; }

        Snake &player2() { return m_p2; }
        const Snake &player2() const { return m_p2; }

        Food &food() { return m_food; }
        const Food &food() const { return m_food; }

        int score1() const { return m_score1; }
        int score2() const { return m_score2; }
        sf::VertexArray DrawGrid(int size, sf::Color c) const ;

    private:
        void startOnePlayer();
        void startTwoPlayers();

        AudioManager &m_audio;
        Mode m_mode = Mode::Menu;
        Snake m_p1, m_p2;
        Food m_food;
        int m_score1 = 0, m_score2 = 0;
        sf::Clock m_clock;
        float m_moveInterval = 0.14f;
    };
}