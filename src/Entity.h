#ifndef BATTLEFROGS_SFML_ENTITY_H
#define BATTLEFROGS_SFML_ENTITY_H

#include "SFML/Config.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace battlefrogs {
    class Obstacle;
    class World;

    class Entity {
    private:
        bool invulnerable = false;
    public:
        enum FACING {
            FACING_LEFT,
            FACING_RIGHT,
        };

        enum Team {
            THE_FRENCH, THE_FROG_PIRATES, SYSTEM
        };

        Entity();

        FACING getFacing();

        virtual void update(World *world, sf::Int32 elapsed) = 0;

        virtual void render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) = 0;

        World *getWorld();

        sf::Rect<float> getPosition();

        bool ignoreCollision();

        Team getTeam();

        float getDamageModifier();

        void decreaseHealth(int amount);

        void setFullHealth(int fullHealth);

        virtual void onObstacleCollision(Obstacle *obstacle);

    protected:
        float damageModifier = 1;
        sf::Int32 currentFrameTime = 0;
        int fullHealth = 100;
        int currentHealth = fullHealth;

        sf::Vector2f startingPoint;
        sf::Vector2f velocity;
        float horizontalSpeed = 8.0f;
        float friction = 0.35f;
        float gravity = 0.75f;
        float jumpSpeed = 30.0f * gravity;

        Team team;
        FACING facing = FACING_RIGHT;
        bool isJumping = false;

        sf::Rect<float> position;

        World *world;

        void move();

        sf::FloatRect getCollisionHitbox(sf::Rect<float> position);

        virtual void die();
        virtual void onCollision(bool collidedHorizontally, bool collidedVertically);

    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_ENTITY_H
