#pragma once // Prevent multiple includes
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

/**
 * @file Bird.h
 * @brief Declares the Bird class, which handles movement and animation of the bird in Flappy Bird.
 */

namespace Flappy
{
    /**
     * @class Bird
     * @brief Represents the bird entity (movement and animation).
     *
     * This class is responsible for:
     * - Managing the bird's sprite
     * - Updating its position with gravity and collisions
     * - Handling flap animation
     */
    class Bird
    {
    public:
        /**
         * @brief Constructor. Initializes the bird with a texture.
         * @param tex Reference to the TextureManager used to retrieve the bird's texture.
         */
        Bird(const TextureManager &tex);

        /**
         * @brief Reset the bird's position and state.
         * @param windowSize Size of the game window.
         */
        void reset(const sf::Vector2u &windowSize);

        /**
         * @brief Make the bird flap (jump) with an impulse force.
         * @param impulse Velocity value applied when jumping.
         */
        void flap(float impulse);

        /**
         * @brief Update the bird's state (movement and animation).
         * @param gravity Gravity value applied to the bird.
         * @param frames Number of frames for the flap animation cycle.
         * @param animate Whether to enable animation.
         * @param physics Whether to apply physics (gravity and velocity).
         */
        void update(float gravity, int frames, bool animate, bool physics);

        /**
         * @brief Get a modifiable reference to the bird's sprite.
         * @return Reference to the bird's sprite.
         */
        sf::Sprite &sprite() { return m_sprite; }

        /**
         * @brief Get a const reference to the bird's sprite (read-only).
         * @return Const reference to the bird's sprite.
         */
        const sf::Sprite &sprite() const { return m_sprite; }

        /**
         * @brief Get the hitbox (collision bounds) of the bird.
         * @return FloatRect representing the bird's bounding box.
         */
        sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }

        /**
         * @brief Get the current position of the bird.
         * @return Vector2f representing the bird's position in the window.
         */
        sf::Vector2f getPosition() const { return m_sprite.getPosition(); }

    private:
        const TextureManager &m_textures; /**< Reference to the TextureManager */
        sf::Sprite m_sprite;              /**< Bird sprite */
        float m_velocity;                 /**< Vertical velocity of the bird */
        int m_frame;                      /**< Current animation frame */
    };
}
