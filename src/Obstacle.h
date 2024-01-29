#ifndef BATTLEFROGS_SFML_OBSTACLE_H
#define BATTLEFROGS_SFML_OBSTACLE_H

#include "Entity.h"

namespace battlefrogs {
    class World;

    class Obstacle : public Entity {
    public:
        Obstacle(World *world, sf::FloatRect collisionBox);
        sf::FloatRect getCollisionHitbox();

    private:
        sf::FloatRect collisionBox;
    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_OBSTACLE_H
