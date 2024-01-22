#include "Entity.h"
#include <iostream>

namespace battlefrogs {
    Entity::Entity() {

    }

    void Entity::setTexture(const std::string& imagePath, int width, int height) {
        if (!texture.loadFromFile(imagePath))
        {
            std::cerr << "Error loading: " << imagePath << std::endl;
        }

        this->width = width;
        this->height = height;

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    }

    void Entity::setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
        sprite.setPosition(position);
    }

    sf::Vector2f Entity::getPosition() {
        return position;
    }
}