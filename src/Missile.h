#ifndef BATTLEFROGS_SFML_MISSILE_H
#define BATTLEFROGS_SFML_MISSILE_H

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace battlefrogs {

    class Missile {
    public:
        Missile(int facing, int startX, int startY);

        void update();

        void move();

        void render(sf::RenderWindow &renderWindow);

    private:
        static const int SPEED = 20;
        int facing = 0;
        sf::Texture texture;
        sf::Sprite sprite;
        float horizontalSpeed = 0;
        sf::Vector2f velocity;
        float friction = 0.35f;

        void updateAnimation();


    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_MISSILE_H
