#include <iostream>
#include "Player.h"
#include "World.h"

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
        // std::cout << "player frame total elapsed = " << currentFrameTime << std::endl;

        // https://stackoverflow.com/questions/72783484/how-to-make-player-animation-in-sfml
        if (currentFrameTime >= ANIMATION_FRAME_RATE[animationType]) {
            sprite.setTextureRect(sf::IntRect(currentFrame * WIDTH, animationType * HEIGHT, WIDTH, HEIGHT));
            currentFrameTime -= ANIMATION_FRAME_RATE[animationType];
            currentFrame = (currentFrame + 1) % ANIMATION_FRAME_COUNT[animationType];
        }
        return sprite;
    }

    sf::Vector2f Player::getPosition() {
        return sprite.getPosition();
    }
}