#include "../include/Snake.h"

namespace Snake
{
    Snake::Snake() {}

    void Snake::init(sf::Vector2f headPos, sf::Color col, sf::Vector2f dir)
    {
        m_body.clear();
        sf::Vector2f size{float(CELL), float(CELL)};
        m_body.push_back(Segment(headPos, size, col));

        for (int i = 1; i < 3; ++i)
        {
            sf::Vector2f bodyPos = {headPos.x - dir.x * i, headPos.y - dir.y * i};
            m_body.push_back(Segment(bodyPos, size, col));
        }

        m_dir = dir;
        m_history.clear();
        m_history.reserve(1024);
    }

    void Snake::update()
    {
        if (m_body.empty())
            return;
        sf::Vector2f newHeadPos = m_body[0].shape.getPosition() + m_dir;
        m_body[0].shape.setPosition(newHeadPos);

        m_history.insert(m_history.begin(), newHeadPos);
        int maxHistory = int(m_body.size()) * m_delay + 10;
        if ((int)m_history.size() > maxHistory)
            m_history.pop_back();

        for (size_t i = 1; i < m_body.size(); ++i)
        {
            int idx = int(i) * m_delay;
            if (idx < (int)m_history.size())
                m_body[i].shape.setPosition(m_history[idx]);
        }
    }

    void Snake::setDirection(sf::Vector2f d)
    {
        if (d + m_dir == sf::Vector2f(0.f, 0.f))
            return;
        m_dir = d;
    }

    sf::Vector2f Snake::getDirection() const { return m_dir; }
    sf::Vector2f Snake::headPos() const { return m_body.empty() ? sf::Vector2f(0.f, 0.f) : m_body[0].shape.getPosition(); }

    void Snake::grow()
    {
        if (m_body.empty())
            return;
        Segment last = m_body.back();
        m_body.push_back(last);
    }

    void Snake::draw(sf::RenderTarget &rt) const
    {
        for (auto &s : m_body)
            rt.draw(s.shape);
    }

    bool Snake::checkSelfCollision() const
    {
        if (m_body.size() < 4)
            return false;
        auto headBounds = m_body[0].shape.getGlobalBounds();
        for (size_t i = 1; i < m_body.size(); ++i)
        {
            if (headBounds.findIntersection(m_body[i].shape.getGlobalBounds()).has_value())
                return true;
        }
        return false;
    }
}
