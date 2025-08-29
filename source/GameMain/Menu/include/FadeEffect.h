#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class FadeEffect
{
public:
    FadeEffect(sf::Vector2u windowSize)
    {
        overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        overlay.setFillColor(sf::Color(0, 0, 0, 0)); // bắt đầu trong suốt
    }

    void startFadeIn(float durationSec)
    {
        mode = Mode::FadeIn;
        timer = 0.f;
        totalTime = durationSec;
    }

    void startFadeOut(float durationSec)
    {
        mode = Mode::FadeOut;
        timer = 0.f;
        totalTime = durationSec;
    }

    void update(float dt)
    {
        if (mode == Mode::None)
            return;

        timer += dt;
        float alpha = 0.f;

        if (mode == Mode::FadeIn)
            alpha = std::min(timer / totalTime * 255.f, 255.f);
        else if (mode == Mode::FadeOut)
            alpha = std::max(255.f - timer / totalTime * 255.f, 0.f);

        overlay.setFillColor(sf::Color(0, 0, 0, static_cast<unsigned char>(alpha)));

        if (timer >= totalTime)
            mode = Mode::None;
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(overlay);
    }

    bool isFading() const { return mode != Mode::None; }

private:
    enum class Mode
    {
        None,
        FadeIn,
        FadeOut
    };
    Mode mode = Mode::None;
    float timer = 0.f;
    float totalTime = 1.f;
    sf::RectangleShape overlay;
};
