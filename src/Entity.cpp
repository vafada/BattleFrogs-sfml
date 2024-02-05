#include <iostream>
#include "Entity.h"
#include "World.h"

namespace battlefrogs {
    Entity::Entity() {

    }

    Entity::FACING Entity::getFacing() {
        return facing;
    }

    void Entity::move() {
        velocity.x *= friction;
        if (abs(velocity.x) < friction) {
            velocity.x = 0;
        }

        if (isJumping) {
            velocity.y += gravity;
        } else {
            velocity.y = 0;
        }

        float newX = position.left + velocity.x;
        float newY = position.top + velocity.y;

        if (newY > (World::FLOOR_LEVEL - position.height)) {
            newY = World::FLOOR_LEVEL - position.height;
        }

        bool collidedHorizontally = false;
        bool collidedVertically = false;
        bool onFloor = false;


        {
            const sf::FloatRect newRect(newX, position.top, position.width, position.height);

            if (!world->isCollision(this, getCollisionHitbox(newRect), false)) {
                position.left = newX;
            } else {
                velocity.x = 0;
                collidedHorizontally = true;
            }
        }

        if (velocity.y < 0) {
            {
                const sf::FloatRect newRect(position.left, newY, position.width, position.height);
                if (!world->isCollision(this, getCollisionHitbox(newRect), false)) {
                    position.top = newY;
                } else {
                    collidedVertically = true;
                }
            }
        } else {
            {
                /*
                if (!world->isCollision(this, getCollisionHitbox(
                        new Rectangle(position.getMinX(), getPosition().getMaxY(), position.getWidth(),
                                      Math.max(velocity.y, gravity))), true)) {
                    position.setLocation(position.getX(), newY);
                } else {
                    velocity.y = 0;
                    collidedVertically = true;
                    onFloor = true;
                }
                 */
            }
        }

        /*
        wasJumping = isJumping;
        wasMoving = isMoving;
        isJumping = !flying && getPosition().getY() < World.FLOOR_LEVEL - getPosition().getHeight() && !onFloor;
        isMoving = Math.abs(velocity.x) > 0;

        if (wasJumping && !isJumping) {
            onLanding();
        }

        updateAnimation();
*/
        if (velocity.x > 0) {
            facing = FACING_RIGHT;
        } else if (velocity.x < 0) {
            facing = FACING_LEFT;
        }
/*
        if (collidedHorizontally || collidedVertically) onCollision(collidedHorizontally, collidedVertically);
         */
    }

    sf::FloatRect Entity::getCollisionHitbox(sf::FloatRect position) {
        return position;
    }

    World *Entity::getWorld() {
        return world;
    }

    sf::Rect<float> Entity::getPosition() {
        return position;
    }

    void Entity::die() {
        world->removeEntity(this);
    }

    bool Entity::ignoreCollision() {
        return false;
    }

    Entity::Team Entity::getTeam() {
        return team;
    }

    float Entity::getDamageModifier() {
        return damageModifier;
    }

    void Entity::decreaseHealth(int amount) {
        if (invulnerable) {
            amount = 0;
        }

        currentHealth -= amount;
        if (currentHealth <= 0) {
            currentHealth = 0;
            die();
        }
    }

    void Entity::setFullHealth(int fullHealth) {
        this->fullHealth = fullHealth;
        if (currentHealth > fullHealth) {
            currentHealth = fullHealth;
        }
    }

} // battlefrogs