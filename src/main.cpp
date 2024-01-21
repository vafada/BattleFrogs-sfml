#include <SFML/Graphics.hpp>
#include "BattleFrogs.h"

int main()
{

    auto window = sf::RenderWindow{ { 1280, 720 }, "BattleFrogs-SFML" };
    window.setFramerateLimit(60);

    battlefrogs::BattleFrogs battleFrogs(window);
    battleFrogs.startPlaying();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }


        }

        window.clear();

        battleFrogs.draw();

        window.display();
    }
}