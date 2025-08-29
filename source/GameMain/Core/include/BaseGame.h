#pragma once
#include "IGame.h"

class BaseGame : public IGame
{
public:
    BaseGame(const std::string &n, sf::Color bg);
    void init(sf::RenderWindow &window) override;
    void run(sf::RenderWindow &window) override;
    void cleanup() override;
    std::string name() const override;

private:
    std::string m_name;
    sf::Color m_bg;

protected:
    sf::Color getBackgroundColor() const { return m_bg; }
};
