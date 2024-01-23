#ifndef BATTLEFROGS_SFML_WORLD_H
#define BATTLEFROGS_SFML_WORLD_H

#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "ForegroundObject.h"

namespace battlefrogs {

    class World {
    private:
        static const int BACKGROUND_COUNT = 8;
        constexpr static const int BACKGROUND_WIDTHS[8] = {
                2000, 2000, 2000, 2000, 2000, 2000, 2000, 709
        };

        sf::Vector2f size;
        sf::Texture starBackground;
        sf::Sprite starBackgroundSprite;

        sf::Texture backgroundTextures[8];
        sf::Sprite backgroundSprites[8];

        std::vector<sf::RectangleShape> collisions;
        std::vector<ForegroundObject> foregroundObjects;

        void loadCollisions();

    public:
        static const int FLOOR_LEVEL = 672;

        World(sf::Vector2f size);

        void render(sf::RenderWindow& renderWindow, sf::View& camera);
        void renderForeground(sf::RenderWindow& renderWindow);
        bool isCollision(sf::RectangleShape& entityHitbox, bool forGravity);
        void addForegroundObjects();
    };

}

#endif
