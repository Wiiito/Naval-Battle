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

    // Buttons
    window.draw(menuBgSprite);
    window.draw(btnSprite);
    window.draw(settingsSprite);
    window.draw(quitSprite);
    // Title
    window.draw(titleTextShadow);
    window.draw(titleText);
    window.draw(codersTextShadow);
    window.draw(codersText);

    window.display();
}