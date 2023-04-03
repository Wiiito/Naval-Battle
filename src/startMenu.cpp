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

    if (isClickBetween(mousePos, btnSprite)) {  // Start game
        controlPanel = 0;
    }
    if (isClickBetween(mousePos, settingsSprite)) {  // Settings
        controlPanel = 1;
    }
    if (isClickBetween(mousePos, languageText) || isClickBetween(mousePos, countryFlagSprite)) {  // Language
        controlPanel = 2;
    }
    if (isClickBetween(mousePos, quitSprite)) {  // Quit
        controlPanel = 3;
    }

    window.clear();

    // Buttons
    window.draw(menuBgSprite);
    window.draw(btnSprite);
    window.draw(settingsSprite);
    window.draw(quitSprite);
    window.draw(languageText);
    window.draw(countryFlagSprite);
    // Title
    window.draw(titleTextShadow);
    window.draw(titleText);
    window.draw(codersTextShadow);
    window.draw(codersText);

    window.display();
}