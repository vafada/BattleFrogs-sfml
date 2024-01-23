#ifndef BATTLEFROGS_SFML_FOREGROUNDOBJECT_H
#define BATTLEFROGS_SFML_FOREGROUNDOBJECT_H

#include <string>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace battlefrogs {

    class ForegroundObject {
    private:
        sf::Texture texture;
        sf::Sprite sprite;
    public:
        ForegroundObject(std::string imagePath, int x, int y, float width, float height);

        void render(sf::RenderWindow& renderWindow);
    };

}

#endif
