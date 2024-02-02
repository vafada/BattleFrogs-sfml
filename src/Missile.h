#ifndef BATTLEFROGS_SFML_MISSILE_H
#define BATTLEFROGS_SFML_MISSILE_H

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Projectile.h"

namespace battlefrogs {
    class World;
    class Missile: public Projectile {
    public:
        Missile(Entity *origin);

        void move(World *world);

        void update(World *world, sf::Int32 elapsed) override;
        void render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) override;

    private:
        static const int SPEED = 20;
        FACING facing = FACING_LEFT;
        sf::Texture texture;
        sf::Sprite sprite;
        float horizontalSpeed = 0;
        float friction = 0.35f;

        void updateAnimation();


    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_MISSILE_H
