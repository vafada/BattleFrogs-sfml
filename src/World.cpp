#include <iostream>
#include <fstream>
#include <sstream>
#include "World.h"

namespace battlefrogs {
    World::World(sf::Vector2f size) : size(size), collisions(39) {
        if (!starBackground.loadFromFile("graphics/starbackground.png")) {
            std::cerr << "Error loading: graphics/starbackground.png" << std::endl;
        }

        starBackgroundSprite.setTexture(starBackground);
        starBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 1801, 540));

        for (int i = 0; i < BACKGROUND_COUNT; i++) {
            if (!backgroundTextures[i].loadFromFile("graphics/background_" + std::to_string(i) + ".png")) {
                std::cerr << "Error loading: graphics/background = " << i << std::endl;
            }
            backgroundSprites[i].setTexture(backgroundTextures[i]);
        }

        loadCollisions();
    }

    void World::render(sf::RenderWindow &renderWindow, sf::View &camera) {
        starBackgroundSprite.setPosition(sf::Vector2f(camera.getCenter().x - (camera.getSize().x / 2), 0));
        renderWindow.draw(starBackgroundSprite);

        int bgx = 0;
        for (int i = 0; i < BACKGROUND_COUNT; i++) {
            backgroundSprites[i].setPosition(bgx, 0);
            renderWindow.draw(backgroundSprites[i]);
            bgx += BACKGROUND_WIDTHS[i];
        }

#ifdef DEBUG
        // draw collision boxes
        for (auto& collisionBox : collisions) {
            renderWindow.draw(collisionBox);
        }
#endif // DEBUG
    }

    void World::loadCollisions() {
        std::ifstream infile("graphics/collisions.txt");
        if (infile.is_open()) {
            std::string line;
            while (std::getline(infile, line)) {
                if (!line.empty()) {
                    char firstLetter = line.at(0);
                    if (firstLetter != '#') {
                        std::istringstream issStream(line);

                        int x;
                        issStream >> x;
                        int y;
                        issStream >> y;
                        int width;
                        issStream >> width;
                        int height;
                        issStream >> height;

                        sf::RectangleShape box(sf::Vector2f(width, height));
                        box.setPosition(x, y);
                        box.setFillColor(sf::Color::Magenta);

                        collisions.push_back(box);
                    }
                }
            }
            infile.close();
        }
    }
}