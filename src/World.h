#ifndef BATTLEFROGS_SFML_WORLD_H
#define BATTLEFROGS_SFML_WORLD_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/View.hpp"

namespace battlefrogs {

    class World {
    private:
        sf::Vector2f size;
        sf::Texture starBackground;
        sf::Sprite sprite;

    public:
        static const int FLOOR_LEVEL = 672;

        World(sf::Vector2f size);

        sf::Sprite getSprite(int x);
    };

}

#endif
