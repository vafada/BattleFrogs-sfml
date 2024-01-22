#include <iostream>
#include "Player.h"
#include "World.h"
#include "SFML/Window/Keyboard.hpp"

namespace battlefrogs {
    Player::Player() {
        if (!texture.loadFromFile("graphics/player.png"))
        {
            std::cerr << "Error loading: graphics/player.png" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, WIDTH, HEIGHT));
        sprite.setPosition(battlefrogs::Player::STARTING_X, battlefrogs::World::FLOOR_LEVEL - HEIGHT);
    }

    int Player::getWalkingAnimation() {
        return hasWeapon ? ANIMATION_TYPE_RUN : ANIMATION_TYPE_WALK;
    }

    sf::Sprite Player::getSprite(sf::Int32 elapsed) {
        currentFrameTime += elapsed;

        int facingMultiplier = facing == FACING_LEFT ? 1 : -1;

        // std::cout << "player frame total elapsed = " << currentFrameTime << std::endl;

        // https://stackoverflow.com/questions/72783484/how-to-make-player-animation-in-sfml
        if (currentFrameTime >= ANIMATION_FRAME_RATE[animationType]) {
            sprite.setTextureRect(sf::IntRect(currentFrame * WIDTH, animationType * HEIGHT, (WIDTH * facingMultiplier), HEIGHT));
            currentFrameTime -= ANIMATION_FRAME_RATE[animationType];
            currentFrame = (currentFrame + 1) % ANIMATION_FRAME_COUNT[animationType];
        }
        return sprite;
    }

    sf::Vector2f Player::getPosition() {
        return sprite.getPosition();
    }

    float Player::getWalkingSpeed() {
        return hasWeapon ? 1.95f : 1.35f;
    }

    void Player::update(sf::Int32 duration) {


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            // left key is pressed: move our character
            std::cout << "In Player.update. Left key pressed" << std::endl;
            velocity.x -= horizontalSpeed * getWalkingSpeed();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            // left key is pressed: move our character
            std::cout << "In Player.update. Right key pressed" << std::endl;
            velocity.x += horizontalSpeed * getWalkingSpeed();
        }

        move();
    }

    void Player::move() {
        velocity.x *= friction;

        if (abs(velocity.x) < friction) {
            velocity.x = 0;
        }

        float newX = sprite.getPosition().x + velocity.x;
        float newY = sprite.getPosition().y + velocity.y;

        //std::cout << "newX = " << newX << std::endl;

        sprite.setPosition(newX, newY);

        wasMoving = isMoving;

        isMoving = abs(velocity.x) > 0;

        if (velocity.x > 0) {
            facing = FACING_RIGHT;
        } else if (velocity.x < 0) {
            facing = FACING_LEFT;
        }

        updateAnimation();
    }

    void Player::updateAnimation() {
        if (wasMoving && !isMoving) {
            animationType = ANIMATION_TYPE_IDLE;
            animationReset();
        } else if (!wasMoving && isMoving) {
            animationType = ANIMATION_TYPE_WALK;
            animationReset();
        }
    }

    void Player::animationReset() {
        currentFrameTime = 0;
        currentFrame = 0;
    }
}