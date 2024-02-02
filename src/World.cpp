#include <iostream>
#include <fstream>
#include <sstream>
#include "World.h"
#include "BattleFrogs.h"

namespace battlefrogs {
    World::World(sf::Vector2f size) : size(size) {
        collisions.reserve(50);
        entities.reserve(100);
        obstacles.reserve(10);
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

        // add doors
        addEntity(
                new Door(this, "graphics/IntoRift_door_Intact.png", 6030, 0, 313, 720,
                         sf::FloatRect(6130, 400, 120, 320)));
        addEntity(new Door(this, "graphics/BakeryWall_door_Intact.png", 11375, 0, 306, 720,
                           sf::FloatRect(11375, 400, 120, 320)));
        addEntity(
                new Door(this, "graphics/Reactor_door_Intact.png", 2135, 0, 502, 720,
                         sf::FloatRect(2135, 400, 120, 320)));


        addForegroundObjects();
    }

    void World::render(sf::RenderWindow &renderWindow, sf::View &camera, sf::Int32 elapsed) {
        starBackgroundSprite.setPosition(sf::Vector2f(camera.getCenter().x - (camera.getSize().x / 2), 0));
        renderWindow.draw(starBackgroundSprite);

        int bgx = 0;
        for (int i = 0; i < BACKGROUND_COUNT; i++) {
            backgroundSprites[i].setPosition(bgx, 0);
            renderWindow.draw(backgroundSprites[i]);
            bgx += BACKGROUND_WIDTHS[i];
        }

        for (const auto &entity: entities) {
            entity->render(renderWindow, elapsed);
        }

        for (auto &foregroundObject: foregroundObjects) {
            foregroundObject->render(renderWindow);
        }

#ifdef DEBUG
        // draw collision boxes
        for (auto &collisionBox: collisions) {
            sf::RectangleShape rectBoxUI(sf::Vector2f(collisionBox.width, collisionBox.height));
            rectBoxUI.setPosition(collisionBox.left, collisionBox.top);
            rectBoxUI.setFillColor(sf::Color::Magenta);
            renderWindow.draw(rectBoxUI);
        }


        for (const auto &obstacle: obstacles) {
            sf::FloatRect collisionBox = obstacle->getCollisionHitbox();
            sf::RectangleShape rectBoxUI(sf::Vector2f(collisionBox.width, collisionBox.height));
            rectBoxUI.setPosition(collisionBox.left, collisionBox.top);
            rectBoxUI.setFillColor(sf::Color::Magenta);
            renderWindow.draw(rectBoxUI);
        }
#endif // DEBUG
    }

    bool World::isCollision(Entity *entity, sf::FloatRect entityHitbox, bool forGravity) {
        for (auto &collisionBox: collisions) {
            if (collisionBox.height == 2 && !forGravity) {
                continue;
            }

            if (collisionBox.intersects(entityHitbox)) {
                return true;
            }
        }

        for (const auto &obstacle: obstacles) {
            if (entityHitbox.intersects(obstacle->getCollisionHitbox())) {
                return true;
            }
        }

        return false;
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

                        if (height == 0) {
                            height = 2;
                        }

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

    void World::update(BattleFrogs *battleFrogs, sf::Int32 duration) {
        for (Entity *entity: entities) {
            entity->update(this, duration);
        }
    }

    void World::removeEntity(Entity *entity) {
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    }

    void World::addEntity(Entity *entity) {
        entities.push_back(entity);
    }

    void World::addObstacle(battlefrogs::Obstacle *obstacle) {
        obstacles.push_back(obstacle);
    }

    void World::removeObstacle(battlefrogs::Obstacle *obstacle) {
        obstacles.erase(std::remove(obstacles.begin(), obstacles.end(), obstacle), obstacles.end());
    }

    Player *World::getPlayer() {
        for (Entity *entity: entities) {
            if (Player *player = dynamic_cast<Player *>(entity)) {
                return player;
            }
        }

        return nullptr;
    }
}