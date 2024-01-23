#include <iostream>
#include "ForegroundObject.h"

namespace battlefrogs {
    ForegroundObject::ForegroundObject(std::string imagePath, int x, int y, float width, float height) {
        if (!texture.loadFromFile(imagePath))
        {
            std::cerr << "Error loading: " << imagePath << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, width, height));
        sprite.setPosition(x, y);
    }

    void ForegroundObject::render(sf::RenderWindow& renderWindow) {
        renderWindow.draw(sprite);
    }
} // battlefrogs