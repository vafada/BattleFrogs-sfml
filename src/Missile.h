#ifndef BATTLEFROGS_SFML_MISSILE_H
#define BATTLEFROGS_SFML_MISSILE_H

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace battlefrogs {

    class Missile {
    public:
        Missile(int facing, int startX, int startY);

    private:
        static const int SPEED = 20;
        int facing = 0;
        sf::Texture texture;
        sf::Sprite sprite;
        float horizontalSpeed = 0;
    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_MISSILE_H
