#include <iostream>
#include "Door.h"

namespace battlefrogs {
    Door::Door(World *world, std::string imagePath, int x, int y, int width, int height, sf::FloatRect collisionBox): Obstacle(world, collisionBox) {
        if (!texture.loadFromFile(imagePath)) {
            std::cerr << imagePath << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, width, height));
        sprite.setPosition(x, y);
    }

    void Door::update(World *world, sf::Int32 elapsed) {

    }

    void Door::render(sf::RenderWindow& renderWindow,  sf::Int32 elapsed) {
        renderWindow.draw(sprite);
    }

    bool Door::intersects(sf::FloatRect anotherBox) {
        return this->collisionBox.intersects(anotherBox);
    }

    sf::FloatRect Door::getCollisionBox() {
        return sf::FloatRect(collisionBox);
    }
} // battlefrogs