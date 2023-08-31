#pragma once
#include "sceneTemp.hpp"

class chooseMode : public SceneTemp
{
public:
    chooseMode(){/*pass*/};
    chooseMode(Vector2u windowSize)
    {
        // Window variables
        this->windowWidth = windowSize.x;
        this->windowHeight = windowSize.y;

        // Creating a scale to font size (16px - 1080p)
        fs = (int)(windowHeight / 67.5);

        // Game Main Texture
        this->mainTexture.loadFromFile("src/assets/sprites.png");

        this->gameSinglePlayerSprite.setTexture(this->mainTexture);
        this->gameSinglePlayerSprite.setTextureRect(IntRect(0, 6 * textureOffset, 13 * textureOffset, 13 * textureOffset));
        this->gameSinglePlayerSprite.setScale((float)this->windowWidth / 1920, (float)windowHeight / 1080);
        this->gameSinglePlayerSprite.setOrigin(this->gameSinglePlayerSprite.getLocalBounds().width / 2, this->gameSinglePlayerSprite.getLocalBounds().height / 2);
        this->gameSinglePlayerSprite.setPosition(this->windowWidth * 1 / 3, this->windowHeight / 2);

        this->gameMultiPlayerSprite.setTexture(this->mainTexture);
        this->gameMultiPlayerSprite.setTextureRect(IntRect(13 * textureOffset, 6 * textureOffset, 13 * textureOffset, 13 * textureOffset));
        this->gameMultiPlayerSprite.setScale((float)this->windowWidth / 1920, (float)windowHeight / 1080);
        this->gameMultiPlayerSprite.setOrigin(this->gameMultiPlayerSprite.getLocalBounds().width / 2, this->gameMultiPlayerSprite.getLocalBounds().height / 2);
        this->gameMultiPlayerSprite.setPosition(this->windowWidth * 2 / 3, this->windowHeight / 2);

        // ---- Game render ----
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

        // this->updateText();
    }

    void update(Engine *pEngine, string *pGameMode)
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->mousePos = Mouse::getPosition(*pEngine->getWindow());
        }

        if (isClickBetween(mousePos, this->gameSinglePlayerSprite))
        {
            pGameMode->replace(0, 0, "S");

            pEngine->setCurrentScene("menu");
        }
        cout << "Dentro: " << *pGameMode << endl;
    };

    void render(RenderWindow *pWindow)
    {
        pWindow->draw(this->gameScreenReference);
        pWindow->draw(this->gameBackgroundSprite);
        pWindow->draw(this->gameSinglePlayerSprite);
        pWindow->draw(this->gameMultiPlayerSprite);
    };
};
