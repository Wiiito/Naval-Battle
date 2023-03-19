#include <iostream>

#include "header.hpp"
// #include "headers/menu.hpp"

Text createText(String text, int posX, int posY) {
    Text startText;
    startText.setFont(font);
    startText.setString(text);
    startText.setCharacterSize(62);
    startText.setFillColor(Color::Black);
    startText.setStyle(Text::Bold);
    startText.setOrigin(startText.getLocalBounds().width / 2, 0 /*startText.getLocalBounds().height / 2*/);
    startText.setPosition(posX, posY);

    return startText;
}

void menu() {
    Vector2i mousePos;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (Mouse::isButtonPressed(Mouse::Left)) {
            mousePos = Mouse::getPosition(window);
            std::cout << "(" << mousePos.x << "," << mousePos.y << ") ";
        }
    }

    window.clear(Color::White);
    window.draw(createText("START", 400, 300));
    window.draw(createText("SETTINGS", 400, 380));
    window.draw(createText("QUIT", 400, 460));
    window.display();
}