#include <unistd.h>

#include "animate.cpp"
#include "header.hpp"

void game() {
    Vector2i mousePos;

    if (restart) {
        bombsLeft = bombsNumber;
        restart = false;
    }

    bool escPressed;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (Mouse::isButtonPressed(Mouse::Left))
            mousePos = Mouse::getPosition(window);
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            escPressed = true;
    }

    if (escPressed) {
        Players.clear();
        Players.shrink_to_fit();
        restart = true;
        controlPanel = 4;
    }

    window.clear();
    window.draw(gameBackgroundSprite);

    // Calculando o tamanho maximo do tabuleiro
    boardSize = Vector2i(gameScreenReference.getLocalBounds().width * gameScreenReference.getScale().x / 2 - 2 * fs,
                         gameScreenReference.getLocalBounds().height * gameScreenReference.getScale().y - 4 * fs);

    if (Players.empty()) {  // Checando se o jogador escolheu o modo de jogo
        window.draw(gameSinglePlayerSprite);
        window.draw(gameMultiPlayerSprite);

        if (isClickBetween(mousePos, gameMultiPlayerSprite)) {
            Player player1;
            Player player2;

            gameMode = "MP";

            Players.push_back(player1);
            Players.push_back(player2);
        } else if (isClickBetween(mousePos, gameSinglePlayerSprite)) {
            Player player1;

            gameMode = "SP";

            Players.push_back(player1);
        }

        window.display();
        return;
    }
    Vector2f rectangleSize((boardSize.x / sizeBoardX) - 2, (boardSize.y / sizeBoardY) - 2);

    Sprite square;
    square.setTexture(texture);
    square.setTextureRect(IntRect(textureOffset, 2 * textureOffset, textureOffset, textureOffset));
    square.setScale(Vector2f(
        (square.getScale().x / textureOffset) * (boardSize.x / sizeBoardX - 2),
        (square.getScale().y / textureOffset) * (boardSize.y / sizeBoardY - 2)));

    // Evitando problemas e facilitador de vidas
    bool click = false;

    for (int i = 0; i < sizeBoardX; i++) {  // Desenhando quadrados na tela e checando hitbox
        for (int j = 0; j < sizeBoardY; j++) {
            // Desenhando na tela
            square.setColor(Color(255, 255, 255, 255));

            // Se ja tiver sido clicado, muda a cor e continua a desenhar
            if (gameMode == "MP" && Players[!currentPlayer].board[i][j]) {
                square.setColor(Color(255, 255, 255, 200));
                square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + 2), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + 2));
                window.draw(square);
                continue;
            } else if (gameMode == "SP" && Players[currentPlayer].board[i][j]) {
                square.setColor(Color(255, 255, 255, 200));
                square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + 2), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + 2));
                window.draw(square);
                continue;
            }

            square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + 2), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + 2));
            window.draw(square);

            // Procurando clique
            if (isClickBetween(mousePos, square) && gameMode == "MP") {
                animate(Vector2i(i, j));
                // Handle click result
                switch (Players[!currentPlayer].hit(Vector2i(i, j))) {
                    case 1:
                        // Acertou mas não destruiu
                        hitSound.play();
                        break;
                    case 2:
                        // Destruiu
                        explodeSound.play();
                        break;
                    case 3:
                        // Ganhou
                        controlPanel = 5;
                        break;
                }

                click = true;
            } else if (isClickBetween(mousePos, square) && gameMode == "SP") {
                animate(Vector2i(i, j));
                switch (Players[currentPlayer].hit(Vector2i(i, j))) {
                    case 1:
                        hitSound.play();
                        // Acertou mas não destruiu
                        break;
                    case 2:
                        // Destruiu
                        explodeSound.play();
                        break;
                    case 3:
                        // Ganhou
                        controlPanel = 5;
                        break;
                }

                click = true;
            }
        }
    }

    // Desenhando foguetes atingidos na tela
    if (gameMode == "MP") {
        Players[!currentPlayer].printBoard();
    } else if (gameMode == "SP") {
        Players[currentPlayer].printBoard();
    }

    if (gameMode == "MP" && currentPlayer == 0) {
        bot.hitPos();
        click = true;
    }

    // Desenhando o jogador atual na tela
    window.draw(playerText);
    Text currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), getFinalPos(playerText).x, getInitialPos(playerText).y, 4, Color::Black);
    window.draw(currentPlayerText);

    // Desenhando quantidade de bombas restantes na tela
    Text bombsLeftText = createText(bombsString + "  " + std::to_string(bombsLeft), getInitialPos(playerText).x, getInitialPos(playerText).y + 6 * fs, 4, Color::Black);
    window.draw(bombsLeftText);

    window.display();

    if (click) {  // Pausando a execução por 2 segundos para a animação e entendimento do player
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

        Sprite square;
        square.setTexture(texture);
        square.setTextureRect(IntRect(textureOffset, 2 * textureOffset, textureOffset, textureOffset));
        square.setScale(Vector2f(
            (square.getScale().x / textureOffset) * (boardSize.x / sizeBoardX - 2),
            (square.getScale().y / textureOffset) * (boardSize.y / sizeBoardY - 2)));

        for (int i = 0; i < sizeBoardX; i++) {
            for (int j = 0; j < sizeBoardY; j++) {
                square.setColor(Color(255, 255, 255, 255));
                if (Players[!currentPlayer].board[i][j]) {
                    square.setColor(Color(255, 255, 255, 200));
                    square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + spacing), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + spacing));
                    window.draw(square);
                    continue;
                }
                square.setPosition(getInitialPos(gameScreenReference).x + 7 * fs + i * (rectangleSize.x + spacing), getInitialPos(gameScreenReference).y + 2 * fs + j * (rectangleSize.y + spacing));
                window.draw(square);
            }
        }

        Players[!currentPlayer].printBoard();
        window.display();

        sleep(1);
        if (currentPlayer) {
            bombsLeft--;
        }
        if (gameMode == "MP") {
            currentPlayer = !currentPlayer;
        }

        if (bombsLeft <= 0) {
            controlPanel = 6;
        }
    }
}