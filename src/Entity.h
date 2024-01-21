#ifndef BATTLEFROGS_SFML_ENTITY_H
#define BATTLEFROGS_SFML_ENTITY_H

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace battlefrogs {

    class Entity {
    public:
        Entity();
        void setTexture(const std::string& imagePath, int width, int height);
        sf::Sprite getSprite();

    protected:
        sf::Texture texture;
        sf::Sprite sprite;
    };

}

#endif
