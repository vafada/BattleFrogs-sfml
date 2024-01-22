#include <iostream>
#include "Player.h"

namespace battlefrogs {
    Player::Player() : Entity() {

    }

    int Player::getWalkingAnimation() {
        return hasWeapon ? ANIMATION_TYPE_RUN : ANIMATION_TYPE_WALK;
    }

    sf::Sprite Player::getSprite(sf::Int32 elapsed) {
        currentFrameTime += elapsed;

        // std::cout << "player frame total elapsed = " << currentFrameTime << std::endl;

        // https://stackoverflow.com/questions/72783484/how-to-make-player-animation-in-sfml
        if (animationType == ANIMATION_TYPE_IDLE) {
            if (currentFrameTime >= ANIMATION_FRAME_RATE[ANIMATION_TYPE_IDLE]) {
                sprite.setTextureRect(sf::IntRect(currentFrame * width, ANIMATION_TYPE_IDLE * height, width, height));
                currentFrameTime -= ANIMATION_FRAME_RATE[ANIMATION_TYPE_IDLE];
                currentFrame = (currentFrame + 1) % ANIMATION_FRAME_COUNT[ANIMATION_TYPE_IDLE];
            }
        }
        return sprite;
    }
}