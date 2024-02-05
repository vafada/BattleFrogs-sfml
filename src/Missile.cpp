#include <iostream>
#include "Missile.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "World.h"

namespace battlefrogs {
    Missile::Missile(Entity *origin) : Projectile(origin, 60, 20, RANGE, DAMAGE) {
        this->world = origin->getWorld();
        if (!texture.loadFromFile("graphics/missile.png")) {
            std::cerr << "graphics/missile.png" << std::endl;
        }

        sprite.setTexture(texture);

        horizontalSpeed = facing == FACING_RIGHT ? SPEED : -SPEED;
    }



    void Missile::update(World *world, sf::Int32 elapsed) {
        Projectile::update(world, elapsed);
    }

    void Missile::render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) {
        //std::cout << "in missle render  = " << position.left <<  std::endl;
        sprite.setTextureRect(sf::IntRect(facing == FACING_RIGHT ? 0 : 60, 0, facing == FACING_RIGHT ? 60 : -60, 29));
        sprite.setPosition(position.left, position.top);
        renderWindow.draw(sprite);
    }

} // battlefrogs