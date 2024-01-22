#include <SFML/Graphics.hpp>
#include <iostream>
#include "BattleFrogs.h"

int main()
{

    auto window = sf::RenderWindow{ { 1280, 720 }, "BattleFrogs-SFML" };
    window.setFramerateLimit(60);

    battlefrogs::BattleFrogs battleFrogs(window);
    battleFrogs.startPlaying();

    sf::Clock clock;

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            /*if (event.type == sf::Event::KeyPressed)
            {

                    std::cout << "scancode: " << event.key.scancode << std::endl;
                    std::cout << "code: " << event.key.code << std::endl;
                    std::cout << "control: " << event.key.control << std::endl;
                    std::cout << "alt: " << event.key.alt << std::endl;
                    std::cout << "shift: " << event.key.shift << std::endl;
                    std::cout << "system: " << event.key.system << std::endl;
                    std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                    std::cout << "localize: " << sf::Keyboard::localize(event.key.scancode) << std::endl;
                    std::cout << "delocalize: " << sf::Keyboard::delocalize(event.key.code) << std::endl;

                    sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            }*/
        }

        window.clear();

        sf::Time elapsed = clock.restart();

        battleFrogs.update(elapsed.asMilliseconds());

        battleFrogs.draw(elapsed.asMilliseconds());

        window.display();
    }
}