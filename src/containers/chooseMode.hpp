#pragma once
#include "sceneTemp.hpp"

class chooseMode : public SceneTemp
{
private:
    bool escPressed = false;

public:
    chooseMode(){/*pass*/};

    void update(Engine *pEngine)
    {
        mousePos = {0, 0};
        if (Mouse::isButtonPressed(Mouse::Left))
            mousePos = Mouse::getPosition(*pEngine->getWindow());
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
            escPressed = true;

        if (isClickBetween(mousePos, gameSinglePlayerSprite))
        {
            gameMode = "SP";

            pEngine->setCurrentScene("game");
        } else if (isClickBetween(mousePos, gameMultiPlayerSprite))
        {
            gameMode = "MP";
            pEngine->setCurrentScene("game");
        } else if (escPressed) {
            pEngine->setCurrentScene("menu");
        }
    };

    void render(RenderWindow *pWindow)
    {
        pWindow->draw(gameScreenReference);
        pWindow->draw(gameBackgroundSprite);
        pWindow->draw(gameSinglePlayerSprite);
        pWindow->draw(gameMultiPlayerSprite);
    };
};
