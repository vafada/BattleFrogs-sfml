#include <iostream>
#include "Door.h"
#include "Player.h"
#include "World.h"

namespace battlefrogs {
    Door::Door(World *world, std::string imagePath, int x, int y, int width, int height, sf::FloatRect collisionBox)
            : Obstacle(world, collisionBox) {
        if (!texture.loadFromFile(imagePath)) {
            std::cerr << imagePath << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, width, height));

        position.left = x;
        position.top = y;
        position.width = width;
        position.height = height;

        sprite.setPosition(x, y);

        setFullHealth(1);
    }

    void Door::update(World *world, sf::Int32 elapsed) {

        sf::FloatRect expandedBox(collisionBox.left - 100, collisionBox.top, collisionBox.width + 200,
                                  collisionBox.height);

        Player *player = world->getPlayer();

        if (player != nullptr) {
            //std::cout << "here" << player << std::endl;
            if (expandedBox.intersects(player->getCollisionBox())) {
                std::cout << "collision with door" << std::endl;
                // TODO
                /*battleFrogs->setTextScreenText(player->getHasWeapon() ? "This door is locked. Blow it up!"
                                                                      : "This door is locked. You need to find the key.");*/
            }
        }
    }

    void Door::render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) {
        renderWindow.draw(sprite);

#ifdef DEBUG
        sf::FloatRect expandedBox(collisionBox.left - 100, collisionBox.top, collisionBox.width + 200,
                                  collisionBox.height);

        sf::RectangleShape rectBoxUI(sf::Vector2f(expandedBox.width, expandedBox.height));
        rectBoxUI.setPosition(expandedBox.left, expandedBox.top);
        rectBoxUI.setFillColor(sf::Color::Blue);
        renderWindow.draw(rectBoxUI);
#endif // DEBUG
    }

    bool Door::intersects(sf::FloatRect anotherBox) {
        return this->collisionBox.intersects(anotherBox);
    }

    sf::FloatRect Door::getCollisionBox() {
        return sf::FloatRect(collisionBox);
    }

    void Door::die() {
        Obstacle::die();
        onDestroyed();
    }

    void Door::onDestroyed() {

    }

} // battlefrogs