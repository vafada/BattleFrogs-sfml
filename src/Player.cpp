#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Player.h"
#include "World.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Audio/Sound.hpp"

namespace battlefrogs {
    Player::Player() {
        if (!texture.loadFromFile("graphics/player.png")) {
            std::cerr << "Error loading: graphics/player.png" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, WIDTH, HEIGHT));
        sprite.setPosition(battlefrogs::Player::STARTING_X, 672 - HEIGHT);

        for (int i = 0; i < 3; i++) {
            std::string waveFile = "sounds/AnnaB_footstep" + std::to_string(i + 1) + ".wav";
            if (!walkingSoundBuffers[i].loadFromFile(waveFile)) {
                std::cerr << "sounds/AnnaB_footstep" + std::to_string(i + 1) << std::endl;
            }
        }
    }

    Player::~Player() {

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

    void Player::update(World *world, sf::Int32 duration) {


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

        playWalkingSound();

        move(world);
    }

    void Player::move(World *world) {
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

        if (newY > (672 - HEIGHT)) {
            newY = 672 - HEIGHT;
        }

        bool collidedHorizontally = false;
        bool collidedVertically = false;
        bool onFloor = false;


        {
            sf::FloatRect playerBox(newX, sprite.getPosition().y, WIDTH, HEIGHT);

            if (!(world->isCollision(playerBox, false))) {
                sprite.setPosition(newX, sprite.getPosition().y);
            } else {
                velocity.x = 0;
                collidedHorizontally = true;
            }
        }

        {
            if (velocity.y < 0) {
                sf::FloatRect playerBox(sprite.getPosition().x, newY, WIDTH, HEIGHT);

                if (!(world->isCollision(playerBox, false))) {
                    sprite.setPosition(sprite.getPosition().x, newY);
                } else {
                    collidedVertically = true;
                }
            } else {
                sf::FloatRect playerBox(sprite.getPosition().x, newY + HEIGHT, WIDTH,
                                        (velocity.y > gravity ? velocity.y : gravity));

                if (world->isCollision(playerBox, true)) {
                    velocity.y = 0;
                    collidedVertically = true;
                    onFloor = true;
                } else {
                    sprite.setPosition(sprite.getPosition().x, newY + 1);
                }
            }

        }


        wasJumping = isJumping;
        wasMoving = isMoving;
        isJumping = (sprite.getPosition().y < 672 - HEIGHT) && !onFloor;

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
        } else if (wasMoving && !isMoving) {
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

    void Player::render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) {
        currentFrameTime += elapsed;

        int facingMultiplier = facing == FACING_LEFT ? 1 : -1;
        int facingXAdd = facing == FACING_LEFT ? 0 : WIDTH;

        // std::cout << "player frame total elapsed = " << currentFrameTime << std::endl;

        // https://stackoverflow.com/questions/72783484/how-to-make-player-animation-in-sfml
        if (currentFrameTime >= ANIMATION_FRAME_RATE[animationType]) {
            sprite.setTextureRect(
                    sf::IntRect((currentFrame * WIDTH) + facingXAdd, animationType * HEIGHT, (WIDTH * facingMultiplier),
                                HEIGHT));
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

    void Player::playWalkingSound() {
        long now = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();

        long soundInterval = hasWeapon ? runningSoundInterval : walkingSoundInterval;

        if (isMoving && !isJumping && now - soundInterval > lastMovingSound) {
            int randomSound = rand() % 3;

            sound.setBuffer(walkingSoundBuffers[randomSound]);
            sound.play();
            lastMovingSound = now;
        }
    }
}