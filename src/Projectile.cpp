#include <iostream>
#include "Projectile.h"

namespace battlefrogs {
    Projectile::Projectile(Entity *origin, float range, int damage) {
        this->startingPoint = this->getProjectilePoint(origin);

        std::cout << "this->startingPoint.x = " << this->startingPoint.x << std::endl;

        position.left = this->startingPoint.x;
        position.top = this->startingPoint.y;

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

        for (Entity entity : world.getCollidingEntities(this)) {
            if (entity.getTeam() != getTeam()) {
                dealDamage(entity);

                if (entity instanceof Enemy) {
                    SoundManager.getInstance().playSoundEffect(frogHitFx);
                }

                die();
                return;
            }
        }

        if ((facing == FACING_RIGHT) && (position.getMinX() >= (startingPoint.getX() + range))) {
            die();
        } else if ((facing == FACING_LEFT) && (position.getMaxX() <= (startingPoint.getX() - range))) {
            die();
        }
         */
    }
} // battlefrogs