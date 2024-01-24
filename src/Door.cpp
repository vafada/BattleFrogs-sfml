#include <iostream>
#include "Door.h"

namespace battlefrogs {
    Door::Door(std::string imagePath, int x, int y, int width, int height, sf::FloatRect collisionBox) {
        if (!texture.loadFromFile(imagePath)) {
            std::cerr << imagePath << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, width, height));
        sprite.setPosition(x, y);

        this->collisionBox = collisionBox;
    }

    void Door::render(sf::RenderWindow& renderWindow) {
        renderWindow.draw(sprite);
    }

    bool Door::intersects(sf::FloatRect anotherBox) {
        return this->collisionBox.intersects(anotherBox);
    }
} // battlefrogs