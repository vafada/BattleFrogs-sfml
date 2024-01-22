#include <iostream>
#include "BattleFrogs.h"

namespace battlefrogs {
    BattleFrogs::BattleFrogs(sf::RenderWindow &window) : renderWindow(window),
                                                         camera(sf::Vector2f(0.0f, 0.0f),
                                                                sf::Vector2f(1280.0f, 720.0f)),
                                                         world(sf::Vector2f(14709, 720)) {
        playing = false;
    }

    void BattleFrogs::startPlaying() {
        this->playing = true;
    }

    void BattleFrogs::draw(sf::Int32 elapsed) {
        camera.setCenter(player.getPosition());

        renderWindow.setView(camera);
        renderWindow.draw(world.getSprite(camera.getCenter().x - (camera.getSize().x / 2)));
        renderWindow.draw(player.getSprite(elapsed));
    }
}