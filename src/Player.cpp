#include <iostream>
#include "Player.h"
#include "World.h"
#include "SFML/Window/Keyboard.hpp"

namespace battlefrogs {
    Player::Player() {
        if (!texture.loadFromFile("graphics/player.png")) {
            std::cerr << "Error loading: graphics/player.png" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, WIDTH, HEIGHT));
        sprite.setPosition(battlefrogs::Player::STARTING_X, battlefrogs::World::FLOOR_LEVEL - HEIGHT);
    }

    int Player::getWalkingAnimation() {
        return hasWeapon ? ANIMATION_TYPE_RUN : ANIMATION_TYPE_WALK;
    }

    sf::Vector2f Player::getPosition() {
        return sprite.getPosition();
    }

    float Player::getWalkingSpeed() {
        return hasWeapon ? 1.95f : 1.35f;
    }

    void Player::update(World &world, sf::Int32 duration) {


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            // left key is pressed: move our character
            velocity.x -= horizontalSpeed * getWalkingSpeed();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            // left key is pressed: move our character
            velocity.x += horizontalSpeed * getWalkingSpeed();
        }

        if (!isJumping && !wasJumping &&
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
            if (velocity.y == 0) {
                // SoundManager.getInstance().playSoundEffect(jumping);
            }
            velocity.y -= jumpSpeed;
            isJumping = true;
            animationType = ANIMATION_TYPE_JUMP;
            animationReset();
            /*animations[animType].start();
            animations[animType].setCurrentFrame(0);
            animations[animType].stopAt(ANIMATION_FRAME_COUNT[animType] - 1);*/
        }

        move(world);
    }

    void Player::move(World &world) {
        velocity.x *= friction;

        if (abs(velocity.x) < friction) {
            velocity.x = 0;
        }

        if (isJumping) {
            velocity.y += gravity;
        } else {
            velocity.y = 0;
        }

        float newX = sprite.getPosition().x + velocity.x;
        float newY = sprite.getPosition().y + velocity.y;

        if (newY > (World::FLOOR_LEVEL - HEIGHT)) {
            newY = World::FLOOR_LEVEL - HEIGHT;
        }

        bool collidedHorizontally = false;
        bool collidedVertically = false;
        bool onFloor = false;


        {
            sf::RectangleShape playerBox(sf::Vector2f(WIDTH, HEIGHT));
            playerBox.setPosition(newX, sprite.getPosition().y);

            if (!world.isCollision(playerBox, false)) {
                sprite.setPosition(newX, sprite.getPosition().y);
            } else {
                velocity.x = 0;
                collidedHorizontally = true;
            }
        }

        if (velocity.y < 0) {
            sf::RectangleShape playerBox(sf::Vector2f(WIDTH, HEIGHT));
            playerBox.setPosition(sprite.getPosition().x, newY);
            if (!world.isCollision(playerBox, false)) {
                sprite.setPosition(sprite.getPosition().x, newY);
            } else {
                collidedVertically = true;
            }
        } else {
            sprite.setPosition(sprite.getPosition().x, newY);
            /*
            sf::RectangleShape playerBox(sf::Vector2f(WIDTH, HEIGHT));
            playerBox.setPosition(sprite.getPosition().x, newY);

            if (!world.isCollision(this, getCollisionHitbox(new Rectangle(position.getMinX(), getPosition().getMaxY(), position.getWidth(), Math.max(velocity.y, gravity))), true)) {
                position.setLocation(position.getX(), newY);
            } else {
                velocity.y = 0;
                collidedVertically = true;
                onFloor = true;
            }
             */
        }


        wasJumping = isJumping;
        wasMoving = isMoving;
        isJumping = sprite.getPosition().y < World::FLOOR_LEVEL - HEIGHT && !onFloor;
        isMoving = abs(velocity.x) > 0;

        if (velocity.x > 0) {
            facing = FACING_RIGHT;
        } else if (velocity.x < 0) {
            facing = FACING_LEFT;
        }

        updateAnimation();
    }

    void Player::updateAnimation() {
        if (wasJumping && !isJumping) {
            animationType = isMoving ? static_cast<ANIMATION_TYPE>(getWalkingAnimation()) : ANIMATION_TYPE_IDLE;
            animationReset();
        } if (wasMoving && !isMoving) {
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

    void Player::render(sf::RenderWindow &renderWindow, sf::View &camera, World &world, sf::Int32 elapsed) {
        currentFrameTime += elapsed;

        int facingMultiplier = facing == FACING_LEFT ? 1 : -1;

        // std::cout << "player frame total elapsed = " << currentFrameTime << std::endl;

        // https://stackoverflow.com/questions/72783484/how-to-make-player-animation-in-sfml
        if (currentFrameTime >= ANIMATION_FRAME_RATE[animationType]) {
            sprite.setTextureRect(
                    sf::IntRect(currentFrame * WIDTH, animationType * HEIGHT, (WIDTH * facingMultiplier), HEIGHT));
            currentFrameTime -= ANIMATION_FRAME_RATE[animationType];
            if (animationType == ANIMATION_TYPE_JUMP) {
                int nextFrame = currentFrame + 1;
                // for the jump animation, we stop at the last frame
                if (nextFrame != ANIMATION_FRAME_COUNT[animationType]) {
                    currentFrame = nextFrame;
                }
            } else {
                currentFrame = (currentFrame + 1) % ANIMATION_FRAME_COUNT[animationType];
            }
        }
        renderWindow.draw(sprite);
    }
}