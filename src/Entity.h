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
        void setPosition(float x, float y);
        virtual sf::Sprite getSprite(sf::Int32 duration) = 0;
        sf::Vector2f getPosition();

    protected:
        sf::Int32 currentFrameTime = 0;
        int height;
        int width;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f position;
    };

}

#endif
