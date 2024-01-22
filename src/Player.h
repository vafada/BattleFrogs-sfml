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

        enum FACING
        {
            FACING_LEFT,
            FACING_RIGHT,
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
        FACING facing = FACING_LEFT;
        int currentFrame = 0;
        sf::Int32 currentFrameTime = 0;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f velocity;
        float horizontalSpeed = 8.0f;
        float friction = 0.35f;

        void move();

        bool isMoving = false;
        bool wasMoving = false;

        void updateAnimation();
        void animationReset();

    public:
        Player();

        int getWalkingAnimation();
        float getWalkingSpeed();

        sf::Sprite getSprite(sf::Int32 elapsed);
        sf::Vector2f getPosition();
        void update(sf::Int32 duration);
    };

}

#endif
