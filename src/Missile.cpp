#include <iostream>
#include "Missile.h"

namespace battlefrogs {
    Missile::Missile(int facing, int startX, int startY): facing(facing) {
        if (!texture.loadFromFile("graphics/missile.png")) {
            std::cerr << "graphics/missile.png" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 60, 29));
        sprite.setPosition(startX, startY);

        horizontalSpeed = facing == 1 ? SPEED : -SPEED;
    }
} // battlefrogs