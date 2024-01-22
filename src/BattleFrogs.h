#ifndef BATTLEFROGS_SFML_BATTLEFROGS_H
#define BATTLEFROGS_SFML_BATTLEFROGS_H

#include "Player.h"
#include "World.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace battlefrogs {

    class BattleFrogs {
    public:
        BattleFrogs(sf::RenderWindow& window);

        void startPlaying();
        void update(sf::Int32 duration);
        void draw(sf::Int32 duration);

    private:
        bool playing;
        World world;
        Player player;
        sf::RenderWindow& renderWindow;
        sf::View camera;
    };

}

#endif
