#ifndef BATTLEFROGS_SFML_PLAYER_H
#define BATTLEFROGS_SFML_PLAYER_H

#include "SFML/System.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace battlefrogs {

    class Player {
    private:
        enum ANIMATION_TYPE
        {
            ANIMATION_TYPE_RUN,
            ANIMATION_TYPE_JUMP,
            ANIMATION_TYPE_IDLE,
            ANIMATION_TYPE_WALK,
            ANIMATION_TYPE_ATTACK,
        };

        constexpr static const int ANIMATION_FRAME_RATE[5] = {
                83, // run
                83, // jump
                166, // idle
                166, // walk
                83, // attack
        };

        constexpr static const int ANIMATION_FRAME_COUNT[5] = {
                6, // run
                3, // jump
                3, // idle
                8, // walk
                7, // attack
        };

        static const int STARTING_X = 6470;

        static const int HEIGHT = 195;
        static const int WIDTH = 152;
        static const int ATTACK_WIDTH = 200;

        bool hasWeapon = false;
        ANIMATION_TYPE animationType = ANIMATION_TYPE_IDLE;
        int currentFrame = 0;
        sf::Int32 currentFrameTime = 0;
        sf::Texture texture;
        sf::Sprite sprite;

    public:
        Player();

        int getWalkingAnimation();

        sf::Sprite getSprite(sf::Int32 elapsed);
        sf::Vector2f getPosition();
    };

}

#endif
