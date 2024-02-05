#include <iostream>
#include "Projectile.h"
#include "World.h"

namespace battlefrogs {
    Projectile::Projectile(Entity *origin, int width, int height, float range, int damage) {
        this->startingPoint = this->getProjectilePoint(origin);

        position.left = this->startingPoint.x;
        position.top = this->startingPoint.y;
        position.width = width;
        position.height = height;

        this->range = range;
        this->damage = damage;

        this->facing = origin->getFacing();
    }

    sf::Vector2f Projectile::getProjectilePoint(Entity *entity) {
        // TODO
        return sf::Vector2f(entity->getPosition().left, entity->getPosition().top + ((195 / 2) - 23));

        /*

        if (entity->getFacing() == Entity::FACING_RIGHT) {

            return new Point(entity.getPosition().getMaxX(), entity.getPosition().getCenterY());
        } else {
            return new Point(entity.getPosition().getMinX() - position.getWidth(), entity.getPosition().getCenterY());
        }
         */
    }


    void Projectile::update(World *world, sf::Int32 elapsed) {
        velocity.x += horizontalSpeed;
        Entity::move();

        /*
        if ((gameContainer.getTime() - lifeStart) >= getMaxLifetime()) {
            die();
            return;
        }
*/
        for (Entity *entity : world->getCollidingEntities(this)) {
            if (entity != nullptr && entity->getTeam() != getTeam()) {
                entity->decreaseHealth((int) (damage * getDamageModifier()));

                // if (entity instanceof Enemy) {
                    // SoundManager.getInstance().playSoundEffect(frogHitFx);
                //}

                die();
                return;
            }
        }

        if ((facing == FACING_RIGHT) && (position.left >= (startingPoint.x + range))) {
            die();
        } else if ((facing == FACING_LEFT) && ((position.left + position.width) <= (startingPoint.x - range))) {
            die();
        }
    }

    void Projectile::onCollision(bool collidedHorizontally, bool collidedVertically) {
        die();
    }

    void Projectile::onObstacleCollision(Obstacle *obstacle) {
        obstacle->decreaseHealth((int) (damage * getDamageModifier()));
    }
} // battlefrogs