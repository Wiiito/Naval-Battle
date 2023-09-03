#pragma once
#include "sceneTemp.hpp"
#include <cmath>

// #include <cwindows>
#include <unistd.h>

class Game : public SceneTemp
{
private:
    bool escPressed;
    vector<Player> Players;
    Vector2i boardSizePx;
    Vector2f rectangleSize;
    Sprite square;
    string gameMode;
    Vector2i squaresCount;
    RenderWindow *pWindow;

    int currentPlayer = 0;
    Text currentPlayerText;
    bool click;

    Text bombsLeftText;

    string bombsString;
    int bombsLeft;
    int bombsNumber;

public:
    Game(){};
    Game(Vector2u windowSize, string gameMode) //, Vector2i squaresCount, int bombsNumber)
    {
        this->gameMode = gameMode;
        this->squaresCount = {10, 10}; // parametro so tava com pregui
        this->bombsNumber = 10;

        this->bombsLeft = this->bombsNumber;

        // Window variables
        this->windowWidth = windowSize.x;
        this->windowHeight = windowSize.y;

        // Creating a scale to font size (16px - 1080p)
        fs = (int)(windowHeight / 67.5);

        // Game Main Texture
        this->mainTexture.loadFromFile("src/assets/sprites.png");

        // ---- Game background ----
        gameBackgroundTx.loadFromFile("src/assets/gameBackground.png");
        gameBackgroundSprite.setTexture(gameBackgroundTx);
        gameBackgroundSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        gameBackgroundSprite.setOrigin(gameBackgroundSprite.getLocalBounds().width / 2, gameBackgroundSprite.getLocalBounds().height / 2);
        gameBackgroundSprite.setPosition(this->windowWidth / 2, this->windowHeight / 2);

        // Game Screen reference
        this->gameScreenReferenceTexture.loadFromFile("src/assets/gameScreen.png");
        this->gameScreenReference.setTexture(this->gameScreenReferenceTexture);
        this->gameScreenReference.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        this->gameScreenReference.setOrigin(this->gameScreenReference.getLocalBounds().width / 2, this->gameScreenReference.getLocalBounds().height / 2);
        this->gameScreenReference.setPosition(this->windowWidth / 2, this->windowHeight / 2);

        // Calculando o tamanho maximo do tabuleiro
        boardSizePx = Vector2i(gameScreenReference.getLocalBounds().width * gameScreenReference.getScale().x / 2 - 2 * fs,
                               gameScreenReference.getLocalBounds().height * gameScreenReference.getScale().y - 4 * fs);

        if (gameMode == "SP")
        { // SinglePlayer
            Players.push_back(
                Player(boardSizePx, squaresCount, &mainTexture, textureOffset, &gameScreenReference, fs));
        }
        else if (gameMode == "MP")
        { // Multiplayer
            for (int i = 0; i < 2; i++)
            {
                Players.push_back(
                    Player(boardSizePx, squaresCount, &mainTexture, textureOffset, &gameScreenReference, fs));
            }
        }

        this->rectangleSize = {float((boardSizePx.x / squaresCount.x) - 2), float((boardSizePx.y / squaresCount.y) - 2)};

        square.setTexture(mainTexture);
        square.setTextureRect(IntRect(textureOffset, 2 * textureOffset, textureOffset, textureOffset));

        square.setScale(Vector2f(
            (square.getScale().x / textureOffset) * (boardSizePx.x / squaresCount.x - 2),
            (square.getScale().y / textureOffset) * (boardSizePx.y / squaresCount.y - 2)));
    
        this->updateText();
    };

    void animate(Vector2i pos, RenderWindow *pWindow)
    {
        // shootSound.play();
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

        float angle = (asin(lado / hipotenusa) * 180 / 3.14159265);

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
            Text currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), (playerText.getGlobalBounds().left + playerText.getGlobalBounds().width), playerText.getGlobalBounds().top, 4, Color::Black);
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
        this->escPressed = false;
        this->pWindow = pEngine->getWindow();

        if (Mouse::isButtonPressed(Mouse::Left))
            this->mousePos = Mouse::getPosition(*pEngine->getWindow());
        else
            this->mousePos = {0, 0};
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            this->escPressed = true;

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
                        // hitSound.play();
                        break;
                    case 2:
                        // Destruiu
                        // explodeSound.play();
                        break;
                    case 3:
                        // Ganhou
                        // controlPanel = 5;
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
                        // hitSound.play();
                        //  Acertou mas não destruiu
                        break;
                    case 2:
                        // Destruiu
                        // explodeSound.play();
                        break;
                    case 3:
                        // Ganhou
                        // controlPanel = 5;
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
        currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), (playerText.getGlobalBounds().left + playerText.getGlobalBounds().width), playerText.getGlobalBounds().top, 4, Color::Black);
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
            cout << (playerText.getGlobalBounds().width) << endl;
            Text currentPlayerText = createText("  0" + std::to_string(currentPlayer + 1), (playerText.getGlobalBounds().left + playerText.getGlobalBounds().width), playerText.getGlobalBounds().top, 4, Color::Black);
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
                // controlPanel = 6;
            }
        }
    };

    void render(sf::RenderWindow *pWindow){
        /*
           if (Players.empty())
               return;

           pWindow->draw(this->gameScreenReference);
           pWindow->draw(this->gameBackgroundSprite);

           for (int i = 0; i < squaresCount.x; i++)
           { // Desenhando quadrados na tela e checando hitbox
               for (int j = 0; j < squaresCount.y; j++)
               {
                   // Desenhando na tela
                   square.setColor(Color(255, 255, 255, 255));

                   square.setPosition((int)gameScreenReference.getGlobalBounds().left + 7 * fs + i * (rectangleSize.x + 2), (int)gameScreenReference.getGlobalBounds().top + 2 * fs + j * (rectangleSize.y + 2));

                   // Se ja tiver sido clicado, muda a cor e continua a desenhar
                   if ((gameMode == "SP" && Players.at(currentPlayer).board[i][j]) || (gameMode == "MP" && Players.at(!currentPlayer).board[i][j]))
                   {
                       square.setColor(Color(255, 255, 255, 200));
                   }

                   pWindow->draw(square);
               }
           }
       */
    };
};