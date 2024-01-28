#include <iostream>
#include <fstream>
#include <sstream>
#include "World.h"
#include "BattleFrogs.h"

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

        // add doors
        this->doors.push_back(new Door("graphics/IntoRift_door_Intact.png", 6030, 0, 313, 720, sf::FloatRect(6130, 400, 120, 320)));
        this->doors.push_back(new Door("graphics/BakeryWall_door_Intact.png", 11375, 0, 306, 720, sf::FloatRect(11375, 400, 120, 320)));
        this->doors.push_back(new Door("graphics/Reactor_door_Intact.png", 2135, 0, 502, 720, sf::FloatRect(2135, 400, 120, 320)));


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

        for (const auto &door: doors) {
            door->render(renderWindow);
        }

        /*for (const auto &missile: missiles) {
            missile->render(renderWindow);
        }*/

        for (const auto &entity: entities) {
            entity->render(renderWindow, elapsed);
        }

        for (auto &foregroundObject: foregroundObjects) {
            foregroundObject->render(renderWindow);
        }

#ifdef DEBUG
        // draw collision boxes
        for (auto& collisionBox : collisions) {
            sf::RectangleShape rectBoxUI(sf::Vector2f(collisionBox.width, collisionBox.height));
            rectBoxUI.setPosition(collisionBox.left, collisionBox.top);
            rectBoxUI.setFillColor(sf::Color::Magenta);
            renderWindow.draw(rectBoxUI);
        }

        for (const auto &door: doors) {
            sf::FloatRect collisionBox = door->getCollisionBox();
            sf::RectangleShape rectBoxUI(sf::Vector2f(collisionBox.width, collisionBox.height));
            rectBoxUI.setPosition(collisionBox.left, collisionBox.top);
            rectBoxUI.setFillColor(sf::Color::Magenta);
            renderWindow.draw(rectBoxUI);
        }
#endif // DEBUG
    }

    void World::renderForeground(sf::RenderWindow &renderWindow) {



    }

    bool World::isCollision(sf::FloatRect& entityHitbox, bool forGravity) {
        for (auto& collisionBox : collisions) {
            if (collisionBox.height == 2 && !forGravity) {
                continue;
            }

            if (collisionBox.intersects(entityHitbox)) {
                return true;
            }
        }

        for (const auto &door: doors) {
            if (door->intersects(entityHitbox)) {
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
        for (const auto &door: doors) {
            sf::FloatRect doorCollisionBox = door->getCollisionBox();
            sf::FloatRect expandedBox(doorCollisionBox.left - 100, doorCollisionBox.top, doorCollisionBox.width + 200, doorCollisionBox.height);
            /*if (expandedBox.intersects(player.getCollisionBox())) {
                battleFrogs->setTextScreenText(player.getHasWeapon() ? "This door is locked. Blow it up!" : "This door is locked. You need to find the key.");
            }*/
        }

        for (const auto &missile: missiles) {
            missile->move(this);
        }

        for (const auto &entity: entities) {
            entity->update(this, duration);
        }
    }

    float World::getPlayerXPosition() {
        //return player.getPosition().x;
    }

    void World::addMissile(Missile *missile) {
        missiles.push_back(missile);
    }

    void World::removeMissile(Missile *missile) {
        missiles.erase(std::remove(missiles.begin(), missiles.end(), missile), missiles.end());
    }

    void World::addEntity(Entity *entity) {
        entities.push_back(entity);
    }
}