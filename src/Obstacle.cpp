#include "Obstacle.h"
#include "World.h"

namespace battlefrogs {
    Obstacle::Obstacle(World *world, sf::FloatRect collisionBox) {
        world->addObstacle(this);
        this->collisionBox = collisionBox;
    }

    sf::FloatRect Obstacle::getCollisionHitbox() {
        return collisionBox;
    }
} // battlefrogs