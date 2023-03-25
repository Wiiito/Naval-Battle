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

    // Por algum motivo, quando declarado fora daqui, a origem do texto não muda
    Text start = createText("START", midWindowWidth, midWindowHeight + 80 * 0);
    Text settings = createText("SETTINGS", midWindowWidth, midWindowHeight + 80 * 1);
    Text quit = createText("QUIT", midWindowWidth, midWindowHeight + 80 * 2);

    // Vendo se o usuario clicou em algum botão
    if (isClickBetween(mousePos, getInitialPos(start), getFinalPos(start))) {
        controlPanel = 0;
    }
    if (isClickBetween(mousePos, getInitialPos(settings), getFinalPos(settings))) {
        controlPanel = 1;
    }
    if (isClickBetween(mousePos, getInitialPos(quit), getFinalPos(quit))) {
        controlPanel = 2;
    }

    window.clear(Color::White);
    window.draw(start);
    window.draw(settings);
    window.draw(quit);
    window.display();
}