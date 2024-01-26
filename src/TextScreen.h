#ifndef BATTLEFROGS_SFML_TEXTSCREEN_H
#define BATTLEFROGS_SFML_TEXTSCREEN_H

#include <string>
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace battlefrogs {

    class TextScreen {
    private:
        static const int TIME_TO_SHOW = 5000;
        std::string message;
        long currentTime;
        sf::Font font;
        sf::Text text;
    public:
        TextScreen();

        void setText(std::string message);
        void render(sf::RenderWindow &renderWindow, int midpoint, sf::Int32 elapsed);
    };

} // battlefrogs

#endif //BATTLEFROGS_SFML_TEXTSCREEN_H
