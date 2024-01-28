#include <iostream>
#include "Missile.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace battlefrogs {
    Missile::Missile(int facing, int startX, int startY): facing(facing) {
        if (!texture.loadFromFile("graphics/missile.png")) {
            std::cerr << "graphics/missile.png" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(facing == 1 ? 0 : 60, 0, facing == 1 ? 60 : -60, 29));
        sprite.setPosition(startX, startY);

        horizontalSpeed = facing == 1 ? SPEED : -SPEED;
    }

    void Missile::update() {
        velocity.x += horizontalSpeed;
        move();
    }

    void Missile::move() {
        velocity.x *= friction;

        if (abs(velocity.x) < friction) {
            velocity.x = 0;
        }

        float newX = sprite.getPosition().x + velocity.x;

        sprite.setPosition(newX, sprite.getPosition().y);

        updateAnimation();
    }

    void Missile::updateAnimation() {

    }

    void Missile::render(sf::RenderWindow& renderWindow) {
        renderWindow.draw(sprite);
    }

} // battlefrogs