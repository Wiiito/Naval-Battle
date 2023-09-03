#pragma once
#include "sceneTemp.hpp"

/*int SceneTemp::fs;
int SceneTemp::windowWidth;
int SceneTemp::windowHeight;*/

class Menu : public SceneTemp
{
public:
  Menu(){/*pass*/};

  void update(Engine *pEngine)
  {
    mousePos = {0, 0};
    if (Mouse::isButtonPressed(Mouse::Left))
    {
      mousePos = Mouse::getPosition(*pEngine->getWindow());
    }

    if (isClickBetween(mousePos, btnSprite))
    { // Start game
      pEngine->setCurrentScene("chooseMode");
    }
    if (isClickBetween(mousePos, settingsSprite))
    { // Settings
      pEngine->setCurrentScene("settings");
    }
    if (isClickBetween(mousePos, languageText) || isClickBetween(mousePos, countryFlagSprite))
    { // Language
      pEngine->setCurrentScene("langMenu"); 
    }
    if (isClickBetween(mousePos, quitSprite))
    { // Quit
      pEngine->getWindow()->close();
    }
  }

  void render(RenderWindow *pWindow)
  {
    pWindow->draw(menuBgSprite);
    pWindow->draw(btnSprite);
    pWindow->draw(settingsSprite);
    pWindow->draw(quitSprite);
    pWindow->draw(languageText);
    pWindow->draw(countryFlagSprite);

    // Title
    pWindow->draw(titleTextShadow);
    pWindow->draw(titleText);
    pWindow->draw(codersTextShadow);
    pWindow->draw(codersText);
  }
};