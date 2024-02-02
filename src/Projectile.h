#ifndef BATTLEFROGS_SFML_PROJECTILE_H
#define BATTLEFROGS_SFML_PROJECTILE_H

#include "Entity.h"

namespace battlefrogs {

    class Projectile: public Entity {
    private:
        int damage;
        float range;

        sf::Vector2f getProjectilePoint(Entity *entity);
    public:
        Projectile(Entity *origin, float range, int damage);
        void update(World *world, sf::Int32 elapsed) override;
    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_PROJECTILE_H
