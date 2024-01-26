#include <iostream>
#include "TextScreen.h"

namespace battlefrogs {
    TextScreen::TextScreen() {
        if (!font.loadFromFile("graphics/Good_Old_DOS.ttf")) {
            std::cerr << "graphics/Good_Old_DOS.ttf" << std::endl;
        }

        text.setFont(font);
    }

    void TextScreen::setText(std::string message) {
        this->message = message;
        text.setString(message);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        currentTime = 0;
    }

    void TextScreen::render(sf::RenderWindow &renderWindow, int midpoint, sf::Int32 elapsed) {
        if (currentTime > TIME_TO_SHOW) {
            return;
        }
        currentTime += elapsed;

        float x = midpoint - (text.getGlobalBounds().width / 2);
        float y = (720 / 3) - (text.getGlobalBounds().height / 2);
        text.setPosition(x, y);
        renderWindow.draw(text);
    }
}