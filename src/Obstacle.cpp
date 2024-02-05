#include "Obstacle.h"
#include "World.h"

namespace battlefrogs {
    Obstacle::Obstacle(World *world, sf::FloatRect collisionBox) {
        this->world = world;
        world->addObstacle(this);
        this->collisionBox = collisionBox;
    }

    sf::FloatRect Obstacle::getCollisionHitbox() {
        return collisionBox;
    }

    void Obstacle::die() {
        Entity::die();
        this->world->removeObstacle(this);
    }
} // battlefrogs