#include "BattleFrogs.h"

namespace battlefrogs {
    BattleFrogs::BattleFrogs(sf::RenderWindow& window) : renderWindow(window)  {
        playing = false;
        player.setTexture("graphics/player.png", 152, 195);
    }

    void BattleFrogs::startPlaying() {
        this->playing = true;
    }

    void BattleFrogs::draw() {
        renderWindow.draw(player.getSprite());
    }
}