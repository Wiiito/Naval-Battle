#include <iostream>

#include "header.hpp"

void menu() {
    Vector2i mousePos;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (Mouse::isButtonPressed(Mouse::Left)) {
            mousePos = Mouse::getPosition(window);
            // std::cout << "(" << mousePos.x << "," << mousePos.y << ") ";
        }
    }
    /*
        // Por algum motivo, quando declarado fora daqui, a origem do texto não muda
        Text startText = createText("START", midWindowWidth, midWindowHeight + 9 * fs * 0, 9, "middle");
        Text settingsText = createText("SETTINGS", midWindowWidth, midWindowHeight + 9 * fs * 1, 9, "middle");
        Text quitText = createText("QUIT", midWindowWidth, midWindowHeight + 9 * fs * 2, 9, "middle");

        // Vendo se o usuario clicou em algum botão
        if (isClickBetween(mousePos, getInitialPos(startText), getFinalPos(startText))) {
            controlPanel = 0;
        }
        if (isClickBetween(mousePos, getInitialPos(settingsText), getFinalPos(settingsText))) {
            controlPanel = 1;
        }
        if (isClickBetween(mousePos, getInitialPos(quitText), getFinalPos(quitText))) {
            controlPanel = 2;
        }
    */

    if (isClickBetween(mousePos, btnSprite)) {
        controlPanel = 0;
    }

    window.clear();
    window.draw(menuBgSprite);
    window.draw(btnSprite);
    window.draw(settings);
    // window.draw(quitText);
    window.display();
}