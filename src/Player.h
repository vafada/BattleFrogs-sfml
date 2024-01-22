#ifndef BATTLEFROGS_SFML_PLAYER_H
#define BATTLEFROGS_SFML_PLAYER_H

#include "Entity.h"

namespace battlefrogs {

    class Player : public Entity {
    private:
        enum ANIMATION_TYPE
        {
            ANIMATION_TYPE_RUN,
            ANIMATION_TYPE_JUMP,
            ANIMATION_TYPE_IDLE,
            ANIMATION_TYPE_WALK,
            ANIMATION_TYPE_ATTACK,
        };

        int ANIMATION_FRAME_RATE[5] = {
                83, // run
                83, // jump
                166, // idle
                166, // walk
                83, // attack
        };

        int ANIMATION_FRAME_COUNT[5] = {
                6, // run
                3, // jump
                3, // idle
                8, // walk
                7, // attack
        };

        bool hasWeapon = false;

        ANIMATION_TYPE animationType = ANIMATION_TYPE_IDLE;

        int currentFrame = 0;

    public:
        static const int STARTING_X = 6470;
        Player();

        int getWalkingAnimation();

        sf::Sprite getSprite(sf::Int32 elapsed) override;
    };

}

#endif
