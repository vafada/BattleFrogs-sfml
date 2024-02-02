#include <iostream>
#include "BattleFrogs.h"

namespace battlefrogs {
    BattleFrogs::BattleFrogs(sf::RenderWindow &window) : renderWindow(window),
                                                         camera(sf::Vector2f(0.0f, 0.0f),
                                                                sf::Vector2f(1280.0f, 720.0f)),
                                                         world(sf::Vector2f(14709, 720)) {
        playing = false;
        textScreen.setText("Use WASD/Arrow keys to move and jump.");
    }

    void BattleFrogs::startPlaying() {
        this->playing = true;
        player = new Player(&world);
        world.addEntity(player);
    }

    void BattleFrogs::update(sf::Int32 duration) {
        world.update(this, duration);
    }

    void BattleFrogs::draw(sf::Int32 elapsed) {
        camera.setCenter(player->getPosition().x, 720 / 2);

        renderWindow.setView(camera);
        world.render(renderWindow, camera, elapsed);

        textScreen.render(renderWindow, player->getPosition().x, elapsed);
    }

    void BattleFrogs::setTextScreenText(std::string message) {
        textScreen.setText(message);
    }
}