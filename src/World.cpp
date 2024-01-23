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
        addForegroundObjects();
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
            sf::RectangleShape rectBoxUI(sf::Vector2f(collisionBox.width, collisionBox.height));
            rectBoxUI.setPosition(collisionBox.left, collisionBox.top);
            rectBoxUI.setFillColor(sf::Color::Magenta);
            renderWindow.draw(rectBoxUI);
        }
#endif // DEBUG
    }

    void World::renderForeground(sf::RenderWindow &renderWindow) {
        for (auto &foregroundObject: foregroundObjects) {
            foregroundObject->render(renderWindow);
        }
    }

    bool World::isCollision(sf::FloatRect& entityHitbox, bool forGravity) {
        for (auto& collisionBox : collisions) {
            if (collisionBox.getSize().y == 0 && !forGravity) {
                continue;
            }

            if (collisionBox.intersects(entityHitbox)) {
                return true;
            }
        }
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

                        sf::FloatRect box(x, y, width, height);

                        collisions.push_back(box);
                    }
                }
            }
            infile.close();
        }
    }

    void World::addForegroundObjects() {
        foregroundObjects.push_back(new ForegroundObject("graphics/LeaveCryo_Door_Broken.png", 8040, 0, 211, 720));
        foregroundObjects.push_back(new ForegroundObject("graphics/BakeryWall_door_Intact.png", 11375, 0, 306, 720));
    }
}