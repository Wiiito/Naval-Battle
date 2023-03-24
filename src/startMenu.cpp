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
    Text start = createText("START", 400, 300);
    Text settings = createText("SETTINGS", 400, 380);
    Text quit = createText("QUIT", 400, 460);

    if (isClickBetween(mousePos, getInitialPos(start), getFinalPos(start))) {
        controlPanel = 1;
    }

    window.clear(Color::White);
    window.draw(start);
    window.draw(settings);
    window.draw(quit);
    window.display();
}