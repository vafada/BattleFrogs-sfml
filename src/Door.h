#ifndef BATTLEFROGS_SFML_DOOR_H
#define BATTLEFROGS_SFML_DOOR_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Obstacle.h"

namespace battlefrogs {

    class Door: public Obstacle {
    private:
        sf::Texture texture;
        sf::Sprite sprite;

    public:
        Door(World *world, std::string imagePath, int x, int y, int width, int height, sf::FloatRect collisionBox);

        void update(World *world, sf::Int32 elapsed) override;
        void render(sf::RenderWindow &renderWindow, sf::Int32 elapsed) override;

        bool intersects(sf::FloatRect anotherBox);

        sf::FloatRect getCollisionBox();
    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_DOOR_H
