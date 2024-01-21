#include <iostream>
#include "World.h"

namespace battlefrogs {
    World::World(sf::Vector2f size) : size(size) {
        if (!starBackground.loadFromFile("graphics/starbackground.png")) {
            std::cerr << "Error loading: graphics/starbackground.png" << std::endl;
        }

        sprite.setTexture(starBackground);
        sprite.setTextureRect(sf::IntRect(0, 0, 1801, 540));
    }

    sf::Sprite World::getSprite(int x) {
        sprite.setPosition(sf::Vector2f(x, 0));
        return sprite;
    }
}