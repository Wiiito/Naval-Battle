#include "header.hpp"

void game() {
    Vector2i mousePos;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (Mouse::isButtonPressed(Mouse::Left))
            mousePos = Mouse::getPosition(window);
    }

    window.clear();
    window.draw(gameBackgroundSprite);

    if (Players.empty()) {  // Checando se o jogador escolheu o modo de jogo
        window.draw(gameSinglePlayerSprite);
        window.draw(gameMultiPlayerSprite);

        if (isClickBetween(mousePos, gameMultiPlayerSprite)) {
            Player player1;
            Player player2;

            Players.push_back(player1);
            Players.push_back(player2);
        }

        window.display();
        return;
    }

    // Calculando o tamanho maximo do tabuleiro
    Vector2f boardSize(gameScreenReference.getLocalBounds().width * gameScreenReference.getScale().x / 2 - 2 * fs,
                       gameScreenReference.getLocalBounds().height * gameScreenReference.getScale().y - 4 * fs);

    // Calculando o tamanho de cada quadrado
    int spacing = 2;
    Vector2f rectangleSize((boardSize.x / sizeBoardX) - spacing, (boardSize.y / sizeBoardY) - spacing);

    for (int i = 0; i < sizeBoardX; i++) {
        for (int j = 0; j < sizeBoardY; j++) {
            RectangleShape square(rectangleSize);
            square.setFillColor(Color::Black);
            square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + spacing), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + spacing));
            window.draw(square);
        }
    }

    window.display();
}
