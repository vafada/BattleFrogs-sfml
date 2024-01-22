#include <iostream>
#include "World.h"

namespace battlefrogs {
    World::World(sf::Vector2f size) : size(size) {
        if (!starBackground.loadFromFile("graphics/starbackground.png")) {
            std::cerr << "Error loading: graphics/starbackground.png" << std::endl;
        }

        starBackgroundSprite.setTexture(starBackground);
        starBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 1801, 540));

        for (int i = 0; i < BACKGROUND_COUNT; i++) {
            if (!backgroundTextures[i].loadFromFile("graphics/background_" +  std::to_string(i) + ".png")) {
                std::cerr << "Error loading: graphics/background = " << i << std::endl;
            }
            backgroundSprites[i].setTexture(backgroundTextures[i]);
        }
    }

    void World::render(sf::RenderWindow& renderWindow, sf::View& camera) {
        starBackgroundSprite.setPosition(sf::Vector2f(camera.getCenter().x - (camera.getSize().x / 2), 0));
        renderWindow.draw(starBackgroundSprite);

        int bgx = 0;
        for (int i = 0; i < BACKGROUND_COUNT; i++) {
            backgroundSprites[i].setPosition(bgx, 0);
            renderWindow.draw(backgroundSprites[i]);
            bgx += BACKGROUND_WIDTHS[i];
        }
    }
}