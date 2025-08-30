#include "../include/GameController.h"
#include <iostream>

namespace Snake
{
    sf::VertexArray GameController::DrawGrid(int size, sf::Color c) const
    {
        sf::VertexArray line(sf::PrimitiveType::Lines);
        for (int i = 0; i <= 1920; i += size)
        {
            sf::Vertex v1;
            v1.color = c;
            v1.position = sf::Vector2f({float(i), 0});
            line.append(v1);
            sf::Vertex v2;
            v2.color = c;
            v2.position = sf::Vector2f({float(i), 1080});
            line.append(v2);
        }
        for (int j = 0; j <= 1080; j += size)
        {
            sf::Vertex v1;
            v1.color = c;
            v1.position = sf::Vector2f(0, float(j));
            line.append(v1);

            sf::Vertex v2;
            v2.color = c;
            v2.position = sf::Vector2f(1920, float(j));
            line.append(v2);
        }
        return line;
    }
    GameController::GameController(AudioManager &audio) : m_audio(audio)
    {
        init();
    }

    void GameController::init()
    {
        m_mode = Mode::Menu;
        m_score1 = m_score2 = 0;
        m_p1 = Snake();
        m_p2 = Snake();
        m_food = Food();
        m_food.spawn(WINDOW_W, WINDOW_H);
        m_clock.restart();
    }

    void GameController::startOnePlayer()
    {
        m_mode = Mode::OnePlayer;
        sf::Vector2f head = {float((WINDOW_W / 2 / CELL) * CELL), float((WINDOW_H / 2 / CELL) * CELL)};
        m_p1.init(head, sf::Color::Green, sf::Vector2f(float(CELL), 0.f));
        m_score1 = 0;
        m_clock.restart();
        m_food.spawn(WINDOW_W, WINDOW_H);
    }

    void GameController::startTwoPlayers()
    {
        m_mode = Mode::TwoPlayers;
        sf::Vector2f head1 = {float((WINDOW_W / 2 / CELL) * CELL), float((WINDOW_H / 2 / CELL) * CELL)};
        sf::Vector2f head2 = {float((WINDOW_W / 2 / CELL) * CELL), float(((WINDOW_H * 2 / 3) / CELL) * CELL)};
        m_p1.init(head1, sf::Color::Green, sf::Vector2f(float(CELL), 0.f));
        m_p2.init(head2, sf::Color::Blue, sf::Vector2f(float(CELL), 0.f));
        m_score1 = m_score2 = 0;
        m_clock.restart();
        m_food.spawn(WINDOW_W, WINDOW_H);
    }

    void GameController::handleEvent(const std::optional<sf::Event> &ev)
    {
        if (!ev)
            return;

        if (m_mode == Mode::Menu)
        {
            if (auto k = ev->getIf<sf::Event::KeyPressed>())
            {
                if (k->code == sf::Keyboard::Key::Num1)
                    startOnePlayer();
                else if (k->code == sf::Keyboard::Key::Num2)
                    startTwoPlayers();
            }
        }
        else if (m_mode == Mode::OnePlayer)
        {
            if (auto k = ev->getIf<sf::Event::KeyPressed>())
            {
                if (k->code == sf::Keyboard::Key::W)
                    m_p1.setDirection({0.f, -float(CELL)});
                else if (k->code == sf::Keyboard::Key::S)
                    m_p1.setDirection({0.f, float(CELL)});
                else if (k->code == sf::Keyboard::Key::A)
                    m_p1.setDirection({-float(CELL), 0.f});
                else if (k->code == sf::Keyboard::Key::D)
                    m_p1.setDirection({float(CELL), 0.f});
                else if (k->code == sf::Keyboard::Key::Escape)
                    m_mode = Mode::Menu;
            }
        }
        else if (m_mode == Mode::TwoPlayers)
        {
            if (auto k = ev->getIf<sf::Event::KeyPressed>())
            {
                if (k->code == sf::Keyboard::Key::W)
                    m_p1.setDirection({0.f, -float(CELL)});
                else if (k->code == sf::Keyboard::Key::S)
                    m_p1.setDirection({0.f, float(CELL)});
                else if (k->code == sf::Keyboard::Key::A)
                    m_p1.setDirection({-float(CELL), 0.f});
                else if (k->code == sf::Keyboard::Key::D)
                    m_p1.setDirection({float(CELL), 0.f});

                else if (k->code == sf::Keyboard::Key::Up)
                    m_p2.setDirection({0.f, -float(CELL)});
                else if (k->code == sf::Keyboard::Key::Down)
                    m_p2.setDirection({0.f, float(CELL)});
                else if (k->code == sf::Keyboard::Key::Left)
                    m_p2.setDirection({-float(CELL), 0.f});
                else if (k->code == sf::Keyboard::Key::Right)
                    m_p2.setDirection({float(CELL), 0.f});

                else if (k->code == sf::Keyboard::Key::Escape)
                    m_mode = Mode::Menu;
            }
        }
        else if (m_mode == Mode::GameOver)
        {
            if (auto k = ev->getIf<sf::Event::KeyPressed>())
            {
                if (k->code == sf::Keyboard::Key::Escape)
                {
                    m_mode = Mode::Menu;
                    m_audio.PlayMusic();
                }
            }
        }
    }

    void GameController::update()
    {
        float elapsed = m_clock.getElapsedTime().asSeconds();
        if (elapsed < m_moveInterval)
            return;
        m_clock.restart();

        auto wrap = [](sf::Vector2f &p)
        {
            if (p.x < 0)
                p.x = float(((WINDOW_W / CELL) - 1) * CELL);
            if (p.x >= (int)WINDOW_W)
                p.x = 0;
            if (p.y < 0)
                p.y = float(((WINDOW_H / CELL) - 1) * CELL);
            if (p.y >= (int)WINDOW_H)
                p.y = 0;
        };

        if (m_mode == Mode::OnePlayer)
        {
            m_p1.update();
            auto hp = m_p1.headPos();
            wrap(hp);
            const_cast<Segment &>(m_p1.body().front()).shape.setPosition(hp);

            if (m_p1.body().front().shape.getGlobalBounds().findIntersection(m_food.bounds()).has_value())
            {
                m_p1.grow();
                m_score1++;
                m_food.spawn(WINDOW_W, WINDOW_H);
                m_audio.PlayEat();
            }
            if (m_p1.checkSelfCollision())
            {
                m_audio.StopMusic();
                m_audio.PlayGameOver();
                m_mode = Mode::GameOver;
            }
        }
        else if (m_mode == Mode::TwoPlayers)
        {
            m_p1.update();
            m_p2.update();

            auto hp1 = m_p1.headPos();
            auto hp2 = m_p2.headPos();
            wrap(hp1);
            wrap(hp2);
            const_cast<Segment &>(m_p1.body().front()).shape.setPosition(hp1);
            const_cast<Segment &>(m_p2.body().front()).shape.setPosition(hp2);

            if (m_p1.body().front().shape.getGlobalBounds().findIntersection(m_food.bounds()).has_value())
            {
                m_p1.grow();
                m_score1++;
                m_food.spawn(WINDOW_W, WINDOW_H);
            }
            if (m_p2.body().front().shape.getGlobalBounds().findIntersection(m_food.bounds()).has_value())
            {
                m_p2.grow();
                m_score2++;
                m_food.spawn(WINDOW_W, WINDOW_H);
            }

            if (m_p1.checkSelfCollision() || m_p2.checkSelfCollision())
                m_mode = Mode::GameOver;

            auto hb1 = m_p1.body().front().shape.getGlobalBounds();
            for (auto &seg : m_p2.body())
                if (hb1.findIntersection(seg.shape.getGlobalBounds()).has_value())
                    m_mode = Mode::GameOver;

            auto hb2 = m_p2.body().front().shape.getGlobalBounds();
            for (auto &seg : m_p1.body())
                if (hb2.findIntersection(seg.shape.getGlobalBounds()).has_value())
                    m_mode = Mode::GameOver;
        }
    }
}