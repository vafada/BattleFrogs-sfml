#include <iostream>
#include "Missile.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "World.h"

namespace battlefrogs {
    Missile::Missile(Entity *origin) : Projectile(origin), facing(origin->getFacing()) {
        this->world = origin->getWorld();
        if (!texture.loadFromFile("graphics/missile.png")) {
            std::cerr << "graphics/missile.png" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(facing == FACING_RIGHT ? 0 : 60, 0, facing == 1 ? 60 : -60, 29));
        //sprite.setPosition(startX, startY);

        horizontalSpeed = facing == FACING_RIGHT ? SPEED : -SPEED;
    }

    void Missile::move(World *world) {
        Projectile::move();
        /*velocity.x += horizontalSpeed;
        velocity.x *= friction;

        if (abs(velocity.x) < friction) {
            velocity.x = 0;
        }

        float newX = sprite.getPosition().x + velocity.x;

        bool collidedHorizontally = false;

        sf::FloatRect missileBox(newX, sprite.getPosition().y, 60, 20);

        if (!(world->isCollision(this, missileBox, false))) {
            sprite.setPosition(newX, sprite.getPosition().y);
        } else {
            velocity.x = 0;
            collidedHorizontally = true;
        }

        updateAnimation();

        if (collidedHorizontally) {
            //onCollision();
            world->removeEntity( this);
        }*/
    }

    void Missile::updateAnimation() {

    }

    void Missile::update(World *world, sf::Int32 elapsed) {
        Projectile::update(world, elapsed);
    }

    void Missile::render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) {
        std::cout << "in missle render  = " << position.left <<  std::endl;
        sprite.setPosition(position.left, position.top);
        renderWindow.draw(sprite);
    }

} // battlefrogs