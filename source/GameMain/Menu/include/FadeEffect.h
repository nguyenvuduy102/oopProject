
/**
 * @file FadeEffect.h
 * @brief Declares the FadeEffect class for fade-in and fade-out effects.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/**
 * @class FadeEffect
 * @brief Handles fade-in and fade-out visual effects.
 */
class FadeEffect
{
public:
    /**
     * @brief Constructs a FadeEffect object.
     * @param windowSize Size of the window for the overlay.
     */
    FadeEffect(sf::Vector2u windowSize)
    {
        overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        overlay.setFillColor(sf::Color(0, 0, 0, 0)); // start transparent
    }

    /**
     * @brief Starts the fade-in effect.
     * @param durationSec Duration of the fade-in in seconds.
     */
    void startFadeIn(float durationSec)
    {
        mode = Mode::FadeIn;
        timer = 0.f;
        totalTime = durationSec;
    }

    /**
     * @brief Starts the fade-out effect.
     * @param durationSec Duration of the fade-out in seconds.
     */
    void startFadeOut(float durationSec)
    {
        mode = Mode::FadeOut;
        timer = 0.f;
        totalTime = durationSec;
    }

    /**
     * @brief Updates the fade effect.
     * @param dt Delta time in seconds.
     */
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

    /**
     * @brief Draws the overlay to the window.
     * @param window Reference to the SFML render window.
     */
    void draw(sf::RenderWindow &window)
    {
        window.draw(overlay);
    }

    /**
     * @brief Checks if a fade effect is active.
     * @return True if fading, false otherwise.
     */
    bool isFading() const { return mode != Mode::None; }

private:
    /**
     * @enum Mode
     * @brief Fade effect modes.
     */
    enum class Mode
    {
        None,    /**< No fade effect. */
        FadeIn,  /**< Fade-in effect. */
        FadeOut  /**< Fade-out effect. */
    };
    Mode mode = Mode::None;           /**< Current fade mode. */
    float timer = 0.f;                /**< Timer for fade effect. */
    float totalTime = 1.f;            /**< Total duration of fade. */
    sf::RectangleShape overlay;       /**< Overlay shape for fade effect. */
};
