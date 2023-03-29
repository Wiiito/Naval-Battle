#include <iostream>

#include "header.hpp"

void menu() {
    Vector2i mousePos;  // Limpando o valor todo frame

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (Mouse::isButtonPressed(Mouse::Left)) {
            mousePos = Mouse::getPosition(window);
        }
    }

    if (isClickBetween(mousePos, btnSprite)) {
        controlPanel = 0;
    }
    if (isClickBetween(mousePos, settingsSprite)) {
        controlPanel = 1;
    }
    if (isClickBetween(mousePos, quitSprite)) {
        controlPanel = 2;
    }

    window.clear();
    window.draw(menuBgSprite);
    window.draw(btnSprite);
    window.draw(settingsSprite);
    window.draw(quitSprite);
    window.display();
}