#include <cmath>

#include "header.hpp"

void animate(Vector2i pos) {
    Clock clock;

    float timeElapsed = clock.getElapsedTime().asSeconds();
    RectangleShape lazerBean;
    lazerBean.setFillColor(Color::Yellow);

    bool firstQuadrant = true;
    bool secondQuadrant = true;
    bool thirdQuadrant = true;
    bool fourthQuadrant = true;

    if (!(pos.x / (sizeBoardX / 2))) {
        firstQuadrant = false;
        fourthQuadrant = false;
    } else {
        secondQuadrant = false;
        thirdQuadrant = false;
    }

    if (!(pos.y / (sizeBoardY / 2))) {
        thirdQuadrant = false;
        fourthQuadrant = false;
    } else {
        firstQuadrant = false;
        secondQuadrant = false;
    }

    // 0 ele fica preso no eixo x
    bool orientToY = rand() % 2;

    Vector2i beanStart;
    Vector2i beanEnd;

    // Setando a casa inicial de acordo com o quadrante
    if (firstQuadrant) {
        beanStart = Vector2i(getInitialPos(gameScreenReference).x + 7 * fs + (rand() % 5 + 5) * orientToY * (boardSize.x / sizeBoardX) + boardSize.x * !orientToY,
        getInitialPos(gameScreenReference).y + 2 * fs + (rand() % 5) * !orientToY * (boardSize.y / sizeBoardY));
    } else if (secondQuadrant) {
        beanStart = Vector2i(getInitialPos(gameScreenReference).x + 7 * fs + (rand() % 5) * orientToY * (boardSize.x / sizeBoardX),
        getInitialPos(gameScreenReference).y + 2 * fs + (rand() % 5) * !orientToY * (boardSize.y / sizeBoardY));
    } else if (thirdQuadrant) {
        beanStart = Vector2i(getInitialPos(gameScreenReference).x + 7 * fs + (rand() % 5) * orientToY * (boardSize.x / sizeBoardX),
        getInitialPos(gameScreenReference).y + 2 * fs + (rand() % 5 + 5) * !orientToY * (boardSize.y / sizeBoardY) + boardSize.y * orientToY);
    } else if (fourthQuadrant) {
        beanStart = Vector2i(getInitialPos(gameScreenReference).x + 7 * fs + (rand() % 5 + 5) * orientToY * (boardSize.x / sizeBoardX) + boardSize.x * !orientToY,
        getInitialPos(gameScreenReference).y + 2 * fs + (rand() % 5 + 5) * !orientToY * (boardSize.y / sizeBoardY) + boardSize.y * orientToY);
    }

    // Calculando o fim do bean
    beanEnd = Vector2i(getInitialPos(gameScreenReference).x + 7 * fs + pos.x * (boardSize.x / sizeBoardX) + (boardSize.x / sizeBoardX) / 2,
                       getInitialPos(gameScreenReference).y + 2 * fs + pos.y * (boardSize.y / sizeBoardY) + (boardSize.y / sizeBoardY) / 2);

    float hipotenusa, baixo, lado;

    baixo = beanEnd.x - beanStart.x;
    lado = beanEnd.y - beanStart.y;
    hipotenusa = sqrt(baixo * baixo + lado * lado);

    while (timeElapsed <= 1) {
        lazerBean.setSize(Vector2f(hipotenusa / 3 * sin(timeElapsed * 3.14159265), 0.5 * fs));
        lazerBean.setOrigin(0, lazerBean.getLocalBounds().height / 2);
        lazerBean.setPosition(beanStart.x + baixo * timeElapsed, beanStart.y + lado * timeElapsed);

        window.clear();
        window.draw(gameBackgroundSprite);

        // Desenhando o jogador atual na tela
        window.draw(playerText);
        Text currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), getFinalPos(playerText).x, getInitialPos(playerText).y, 4, Color::Black);
        window.draw(currentPlayerText);

        // Desenhando quantidade de bombas restantes na tela
        Text bombsLeftText = createText(bombsString + "  " + std::to_string(bombsLeft), getInitialPos(playerText).x, getInitialPos(playerText).y + 6 * fs, 4, Color::Black);
        window.draw(bombsLeftText);

        // Calculando o tamanho de cada quadrado
        int spacing = 2;
        Vector2f rectangleSize((boardSize.x / sizeBoardX) - spacing, (boardSize.y / sizeBoardY) - spacing);

        RectangleShape square(rectangleSize);
        for (int i = 0; i < sizeBoardX; i++) {
            for (int j = 0; j < sizeBoardY; j++) {
                square.setFillColor(Color::Black);
                if (Players[!currentPlayer].board[i][j]) {
                    square.setFillColor(Color(0, 0, 0, 200));
                    square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + spacing), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + spacing));
                    window.draw(square);
                    continue;
                }
                square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + spacing), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + spacing));
                window.draw(square);
            }
        }

        Players[!currentPlayer].printBoard();

        window.draw(lazerBean);
        
        timeElapsed = clock.getElapsedTime().asSeconds();
        window.display();
    }
}