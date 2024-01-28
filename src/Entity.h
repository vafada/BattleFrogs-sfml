#ifndef BATTLEFROGS_SFML_ENTITY_H
#define BATTLEFROGS_SFML_ENTITY_H

#include "SFML/Config.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace battlefrogs {
    class World;
    class Entity {
    public:
        enum FACING {
            FACING_LEFT,
            FACING_RIGHT,
        };

        Entity();

        virtual void update(World *world, sf::Int32 elapsed) = 0;
        virtual void render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) = 0;

    protected:
        sf::Int32 currentFrameTime = 0;

        float horizontalSpeed = 8.0f;
        float friction = 0.35f;
        float gravity = 0.75f;
        float jumpSpeed = 30.0f * gravity;

        FACING facing = FACING_LEFT;


    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_ENTITY_H
