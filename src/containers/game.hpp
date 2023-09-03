#pragma once
#include "sceneTemp.hpp"
#include <cmath>

#if defined(__linux__)
    #include <unistd.h> // sleep in Linux
#elif _WIN32
    #include <cwindows> // sleep in Windows
#endif

class Game : public SceneTemp
{
private:
    bool escPressed;
    vector<Player> Players;
    Vector2f rectangleSize;
    Sprite square;
    RenderWindow *pWindow;

    int currentPlayer = 0;
    Text currentPlayerText;
    bool click;

    Text bombsLeftText;

    string bombsString;
    int bombsLeft;

public:
    Game()
    {
        bombsLeft = bombsNumber;

        if (gameMode == "SP")
        { // SinglePlayer
            Players.push_back(
                Player(boatsQuantity, boardSizePx, squaresCount, &mainTexture, textureOffset, &gameScreenReference, fs));
        }
        else if (gameMode == "MP")
        { // Multiplayer
            for (int i = 0; i < 2; i++)
            {
                Players.push_back(
                Player(boatsQuantity, boardSizePx, squaresCount, &mainTexture, textureOffset, &gameScreenReference, fs));
            }
        }

        rectangleSize = {float((boardSizePx.x / squaresCount.x) - 2), float((boardSizePx.y / squaresCount.y) - 2)};

        square.setTexture(mainTexture);
        square.setTextureRect(IntRect(textureOffset, 2 * textureOffset, textureOffset, textureOffset));

        square.setScale(Vector2f(
            (square.getScale().x / textureOffset) * (boardSizePx.x / squaresCount.x - 2),
            (square.getScale().y / textureOffset) * (boardSizePx.y / squaresCount.y - 2)));
    };

    void animate(Vector2i pos, RenderWindow *pWindow)
    {
        shootSound.play();
        Clock clock;

        float timeElapsed = clock.getElapsedTime().asSeconds();
        RectangleShape lazerBean;

        lazerBean.setFillColor(Color(46, 103, 248));

        if (currentPlayer)
        {
            lazerBean.setFillColor(Color(235, 33, 46));
        }

        bool firstQuadrant = true;
        bool secondQuadrant = true;
        bool thirdQuadrant = true;
        bool fourthQuadrant = true;

        if (!(pos.x / (squaresCount.x / 2)))
        {
            firstQuadrant = false;
            fourthQuadrant = false;
        }
        else
        {
            secondQuadrant = false;
            thirdQuadrant = false;
        }

        if (!(pos.y / (squaresCount.y / 2)))
        {
            thirdQuadrant = false;
            fourthQuadrant = false;
        }
        else
        {
            firstQuadrant = false;
            secondQuadrant = false;
        }

        // 0 ele fica preso no eixo x
        bool orientToY = rand() % 2;

        Vector2i beanStart;
        Vector2i beanEnd;

        // Setando a casa inicial de acordo com o quadrante
        if (firstQuadrant)
        {
            beanStart = Vector2i(gameScreenReference.getGlobalBounds().left + 7 * fs + (rand() % squaresCount.x / 2 + squaresCount.x / 2) * orientToY * (boardSizePx.x / squaresCount.x) + boardSizePx.x * !orientToY,
                                 gameScreenReference.getGlobalBounds().top + 2 * fs + (rand() % squaresCount.y / 2) * !orientToY * (boardSizePx.y / squaresCount.y));
        }
        else if (secondQuadrant)
        {
            beanStart = Vector2i(gameScreenReference.getGlobalBounds().left + 7 * fs + (rand() % squaresCount.x / 2) * orientToY * (boardSizePx.x / squaresCount.x),
                                 gameScreenReference.getGlobalBounds().top + 2 * fs + (rand() % squaresCount.y / 2) * !orientToY * (boardSizePx.y / squaresCount.y));
        }
        else if (thirdQuadrant)
        {
            beanStart = Vector2i(gameScreenReference.getGlobalBounds().left + 7 * fs + (rand() % squaresCount.x / 2) * orientToY * (boardSizePx.x / squaresCount.x),
                                 gameScreenReference.getGlobalBounds().top + 2 * fs + (rand() % squaresCount.y / 2 + squaresCount.y / 2) * !orientToY * (boardSizePx.y / squaresCount.y) + boardSizePx.y * orientToY);
        }
        else if (fourthQuadrant)
        {
            beanStart = Vector2i(gameScreenReference.getGlobalBounds().left + 7 * fs + (rand() % squaresCount.x / 2 + squaresCount.x / 2) * orientToY * (boardSizePx.x / squaresCount.x) + boardSizePx.x * !orientToY,
                                 gameScreenReference.getGlobalBounds().top + 2 * fs + (rand() % squaresCount.y / 2 + squaresCount.y / 2) * !orientToY * (boardSizePx.y / squaresCount.y) + boardSizePx.y * orientToY);
        }

        // Calculando o fim do bean
        beanEnd = Vector2i(gameScreenReference.getGlobalBounds().left + 7 * fs + pos.x * (boardSizePx.x / squaresCount.x) + (boardSizePx.x / squaresCount.x) / 2,
                           gameScreenReference.getGlobalBounds().top + 2 * fs + pos.y * (boardSizePx.y / squaresCount.y) + (boardSizePx.y / squaresCount.y) / 2);

        float hipotenusa, baixo, lado;

        baixo = beanEnd.x - beanStart.x;
        lado = beanEnd.y - beanStart.y;
        hipotenusa = sqrt(baixo * baixo + lado * lado);

        float angle = (asin(lado / hipotenusa) * 180 / 3.14159265); // O Flavio saberia colocar mais 100 casa de cabeça, nmrl, nerd dms

        if (beanEnd.x < beanStart.x)
        {
            angle = 180 - angle;
        }

        lazerBean.setRotation(angle);

        while (timeElapsed <= 1)
        {
            lazerBean.setSize(Vector2f(hipotenusa / 3 * sin(timeElapsed * 3.14159265), 0.25 * fs));
            lazerBean.setOrigin(0, lazerBean.getLocalBounds().height / 2);
            lazerBean.setPosition(beanStart.x + baixo * timeElapsed, beanStart.y + lado * timeElapsed);

            pWindow->clear();
            pWindow->draw(gameBackgroundSprite);

            // Desenhando o jogador atual na tela
            pWindow->draw(playerText);
            currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), (playerText.getGlobalBounds().left + playerText.getGlobalBounds().width), playerText.getGlobalBounds().top - fs, 4, Color::Black);
            pWindow->draw(currentPlayerText);

            // Desenhando quantidade de bombas restantes na tela
            Text bombsLeftText = createText(bombsString + "  " + std::to_string(bombsLeft), playerText.getGlobalBounds().left, playerText.getGlobalBounds().top + 6 * fs, 4, Color::Black);
            pWindow->draw(bombsLeftText);

            // Calculando o tamanho de cada quadrado
            int spacing = 2;
            Vector2f rectangleSize((boardSizePx.x / squaresCount.x) - spacing, (boardSizePx.y / squaresCount.y) - spacing);

            Sprite square;
            square.setTexture(mainTexture);
            square.setTextureRect(IntRect(textureOffset, 2 * textureOffset, textureOffset, textureOffset));
            square.setScale(Vector2f(
                (square.getScale().x / textureOffset) * (boardSizePx.x / squaresCount.x - 2),
                (square.getScale().y / textureOffset) * (boardSizePx.y / squaresCount.y - 2)));

            for (int i = 0; i < squaresCount.x; i++)
            {
                for (int j = 0; j < squaresCount.y; j++)
                {
                    square.setColor(Color(255, 255, 255, 255));
                    if (Players[!currentPlayer * (Players.size() - 1)].board[i][j])
                    {
                        square.setColor(Color(255, 255, 255, 200));
                        square.setPosition(gameScreenReference.getGlobalBounds().left + 7 * fs + i * (rectangleSize.x + spacing), gameScreenReference.getGlobalBounds().top + 2 * fs + j * (rectangleSize.y + spacing));
                        pWindow->draw(square);
                        continue;
                    }
                    square.setPosition(gameScreenReference.getGlobalBounds().left + 7 * fs + i * (rectangleSize.x + spacing), gameScreenReference.getGlobalBounds().top + 2 * fs + j * (rectangleSize.y + spacing));
                    pWindow->draw(square);
                }
            }

            Players[!currentPlayer * (Players.size() - 1)].printBoard(pWindow);

            pWindow->draw(lazerBean);

            timeElapsed = clock.getElapsedTime().asSeconds();
            pWindow->display();
        }
    }

    void update(Engine *pEngine)
    {
        escPressed = false;
        pWindow = pEngine->getWindow();

        if (Mouse::isButtonPressed(Mouse::Left))
            mousePos = Mouse::getPosition(*pEngine->getWindow());
        else
            mousePos = {0, 0};
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            escPressed = true;

        if (escPressed)
        {
            Players.clear();
            Players.shrink_to_fit();
            bombsLeft = bombsNumber;
            pEngine->setCurrentScene("menu");
            return;
        }

        pWindow->clear();
        pWindow->draw(gameBackgroundSprite);

        click = false;

        for (int i = 0; i < squaresCount.x; i++)
        { // Desenhando quadrados na tela e checando hitbox
            for (int j = 0; j < squaresCount.y; j++)
            {
                // Desenhando na tela
                square.setColor(Color(255, 255, 255, 255));

                square.setPosition(gameScreenReference.getGlobalBounds().left + 7 * fs + i * (rectangleSize.x + 2), gameScreenReference.getGlobalBounds().top + 2 * fs + j * (rectangleSize.y + 2));

                // Se ja tiver sido clicado, muda a cor e continua a desenhar
                if ((gameMode == "SP" && Players.at(currentPlayer).board[i][j]) || (gameMode == "MP" && Players.at(!currentPlayer).board[i][j]))
                {
                    square.setColor(Color(255, 255, 255, 200));
                }

                pWindow->draw(square);

                // Procurando clique
                if (isClickBetween(mousePos, square) && gameMode == "MP")
                {
                    animate(Vector2i(i, j), pEngine->getWindow());
                    //  Handle click result
                    switch (Players[!currentPlayer].hit(Vector2i(i, j)))
                    {
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
                        win = true;
                        pEngine->setCurrentScene("finalScreen");
                        return;
                        break;
                    }

                    click = true;
                }
                else if (isClickBetween(mousePos, square) && gameMode == "SP")
                {
                    animate(Vector2i(i, j), pEngine->getWindow());
                    switch (Players[currentPlayer].hit(Vector2i(i, j)))
                    {
                    case 1:
                        //  Acertou mas não destruiu
                        hitSound.play();
                        break;
                    case 2:
                        // Destruiu
                        explodeSound.play();
                        break;
                    case 3:
                        // Ganhou
                        win = true;
                        pEngine->setCurrentScene("finalScreen");
                        return;
                        break;
                    }

                    click = true;
                }
            }
        }

        // Desenhando foguetes atingidos na tela
        if (gameMode == "MP")
        {
            Players.at(!currentPlayer).printBoard(pEngine->getWindow());
        }
        else if (gameMode == "SP")
        {
            Players.at(currentPlayer).printBoard(pEngine->getWindow());
        }

        // Desenhando o jogador atual na tela
        pWindow->draw(playerText);
        currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), (playerText.getGlobalBounds().left + playerText.getGlobalBounds().width), playerText.getGlobalBounds().top - fs, 4, Color::Black);
        pWindow->draw(currentPlayerText);

        // Desenhando quantidade de bombas restantes na tela
        bombsLeftText = createText(bombsString + "  " + std::to_string(bombsLeft), playerText.getGlobalBounds().left, playerText.getGlobalBounds().top + 6 * fs, 4, Color::Black);
        pWindow->draw(bombsLeftText);

        pWindow->display();

        if (click)
        { // Pausando a execução por 2 segundos para a animação e entendimento do player
            pWindow->clear();
            pWindow->draw(gameBackgroundSprite);

            // Desenhando o jogador atual na tela
            pWindow->draw(playerText);
            currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), (playerText.getGlobalBounds().left + playerText.getGlobalBounds().width), playerText.getGlobalBounds().top - fs, 4, Color::Black);
            pWindow->draw(currentPlayerText);

            // Desenhando quantidade de bombas restantes na tela
            Text bombsLeftText = createText(bombsString + "  " + std::to_string(bombsLeft), playerText.getGlobalBounds().left, playerText.getGlobalBounds().top + 6 * fs, 4, Color::Black);
            pWindow->draw(bombsLeftText);

            // Calculando o tamanho de cada quadrado
            int spacing = 2;
            Vector2f rectangleSize((boardSizePx.x / squaresCount.x) - spacing, (boardSizePx.y / squaresCount.y) - spacing);

            Sprite square;
            square.setTexture(mainTexture);
            square.setTextureRect(IntRect(textureOffset, 2 * textureOffset, textureOffset, textureOffset));
            square.setScale(Vector2f(
                (square.getScale().x / textureOffset) * (boardSizePx.x / squaresCount.x - 2),
                (square.getScale().y / textureOffset) * (boardSizePx.y / squaresCount.y - 2)));

            for (int i = 0; i < squaresCount.x; i++)
            {
                for (int j = 0; j < squaresCount.y; j++)
                {
                    square.setColor(Color(255, 255, 255, 255));
                    if (Players[!currentPlayer * (Players.size() - 1)].board[i][j])
                    {
                        square.setColor(Color(255, 255, 255, 200));
                        square.setPosition(gameScreenReference.getGlobalBounds().left + 7 * fs + i * (rectangleSize.x + spacing), gameScreenReference.getGlobalBounds().top + 2 * fs + j * (rectangleSize.y + spacing));
                        pWindow->draw(square);
                        continue;
                    }
                    square.setPosition(gameScreenReference.getGlobalBounds().left + 7 * fs + i * (rectangleSize.x + spacing), gameScreenReference.getGlobalBounds().top + 2 * fs + j * (rectangleSize.y + spacing));
                    pWindow->draw(square);
                }
            }

            Players[!currentPlayer * (Players.size() - 1)].printBoard(pEngine->getWindow());
            pWindow->display();

            sleep(1);
            if (currentPlayer || gameMode == "SP")
            {
                bombsLeft--;
            }
            if (gameMode == "MP")
            {
                currentPlayer = !currentPlayer;
            }

            if (bombsLeft <= 0)
            {
                win = false;
                pEngine->setCurrentScene("finalScreen");
            }
        }
    };
};