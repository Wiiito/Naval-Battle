#include "header.hpp"

void loseScreen() {
    Players.clear();
    Players.shrink_to_fit();
    restart = true;
    
    Vector2i mousePos;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (Mouse::isButtonPressed(Mouse::Left))
            mousePos = Mouse::getPosition(window);
    }
    

    currentPlayer = 0;
    window.clear();
        if (isClickBetween(mousePos, endScreenBackButton)) {
        controlPanel = 4;
    }
    if (isClickBetween(mousePos, endScreenPlayAgain)) {
        controlPanel = 0;
    }
    window.draw(gameBackgroundSprite);
    window.draw(endScreenBackButton);
    window.draw(endScreenPlayAgain);
    window.draw(loseText);
    window.display();
}