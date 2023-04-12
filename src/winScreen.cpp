#include "header.hpp"

void winScreen() {
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

    Text playerCongratsText = createText(congratulationsText.getString() + " " + playerText.getString() + " " + std::to_string(!currentPlayer + 1) + ", " + wonString + "!", midWindowWidth, getInitialPos(gameScreenReference).y + 15 * fs, 5, Color::Black, "Anteb", "middle");

    if (isClickBetween(mousePos, endScreenBackButton)) {
        controlPanel = 4;
    }
    if (isClickBetween(mousePos, endScreenPlayAgain)) {
        currentPlayer = 0;
        controlPanel = 0;
    }

    window.clear();
    window.draw(gameBackgroundSprite);
    window.draw(congratulationsText);
    window.draw(playerCongratsText);
    window.draw(endScreenBackButton);
    window.draw(endScreenPlayAgain);
    window.display();
}