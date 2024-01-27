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
#include "Door.h"
#include "Player.h"


namespace battlefrogs {
    class BattleFrogs;

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

        std::vector<sf::FloatRect> collisions;
        std::vector<ForegroundObject*> foregroundObjects;
        std::vector<Door*> doors;

        Player player;

        void loadCollisions();

    public:
        static const int FLOOR_LEVEL = 672;

        World(sf::Vector2f size);

        void render(sf::RenderWindow& renderWindow, sf::View& camera, sf::Int32 elapsed);
        void renderForeground(sf::RenderWindow& renderWindow);
        bool isCollision(sf::FloatRect& entityHitbox, bool forGravity);
        void addForegroundObjects();

        void update(BattleFrogs *battleFrogs, sf::Int32 duration);

        float getPlayerXPosition();
    };

}

#endif
