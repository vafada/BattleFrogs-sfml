#ifndef BATTLEFROGS_SFML_DOOR_H
#define BATTLEFROGS_SFML_DOOR_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace battlefrogs {

    class Door {
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::FloatRect collisionBox;

    public:
        Door(std::string imagePath, int x, int y, int width, int height, sf::FloatRect collisionBox);

        void render(sf::RenderWindow& renderWindow);

        bool intersects(sf::FloatRect anotherBox);
    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_DOOR_H
