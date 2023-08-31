#pragma once
#include "sceneTemp.hpp"

class Menu : public SceneTemp
{
public:
  Menu(){/*pass*/};
  Menu(Vector2u windowSize)
  {
    // Window variables
    this->windowWidth = windowSize.x;
    this->windowHeight = windowSize.y;

    // Creating a scale to font size (16px - 1080p)
    fs = (int)(windowHeight / 67.5);

    // Game Main Texture
    this->mainTexture.loadFromFile("src/assets/sprites.png");

    // Flags texture
    this->flagsTexture.loadFromFile("src/assets/flags.png");

    // Fonte initialization
    fontAnteb.loadFromFile("src/assets/fonts/Anteb-Regular.ttf");
    fontBlanka.loadFromFile("src/assets/fonts/Blanka-Regular.otf");
    fontMontserrat.loadFromFile("src/assets/fonts/Montserrat.OTF");

    // Background
    this->menuBgTx.loadFromFile("src/assets/menuBackground.png");
    this->menuBgSprite.setTexture(this->menuBgTx);
    this->menuBgSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    this->menuBgSprite.setOrigin(this->menuBgSprite.getLocalBounds().width / 2, this->menuBgSprite.getLocalBounds().height / 2);
    this->menuBgSprite.setPosition(windowWidth / 2, windowHeight / 2);

    // Start Button
    this->btnSprite.setTexture(this->mainTexture);
    this->btnSprite.setTextureRect(IntRect(0, 3 * this->textureOffset, 9 * this->textureOffset, 3 * this->textureOffset));
    this->btnSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    this->btnSprite.setOrigin(this->btnSprite.getLocalBounds().width / 2, this->btnSprite.getLocalBounds().height / 2);
    this->btnSprite.setPosition(windowWidth * 50 / 100, windowHeight * 78 / 100);

    // Settings Button
    this->settingsSprite.setTexture(this->mainTexture);
    this->settingsSprite.setTextureRect(IntRect(4 * this->textureOffset, 0, 2 * this->textureOffset, 2 * this->textureOffset));
    this->settingsSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    this->settingsSprite.setOrigin(0, this->settingsSprite.getLocalBounds().height);
    this->settingsSprite.setPosition(windowWidth * 2 / 100, windowHeight * 96 / 100);

    // Quit Button
    this->quitSprite.setTexture(this->mainTexture);
    this->quitSprite.setTextureRect(IntRect(6 * this->textureOffset, 0, 2 * this->textureOffset, 2 * this->textureOffset));
    this->quitSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    this->quitSprite.setOrigin(this->quitSprite.getLocalBounds().width, this->quitSprite.getLocalBounds().height);
    this->quitSprite.setPosition(windowWidth * 98 / 100, windowHeight * 96 / 100);

    this->updateText();
  }

  void update(Engine *pEngine)
  {
    if (Mouse::isButtonPressed(Mouse::Left))
    {
      this->mousePos = Mouse::getPosition(*pEngine->getWindow());
    }

    if (isClickBetween(mousePos, btnSprite))
    { // Start game
      pEngine->setCurrentScene("chooseMode");
    }
    if (isClickBetween(mousePos, settingsSprite))
    { // Settings
      /*pass*/
    }
    /*if (isClickBetween(mousePos, languageText) || isClickBetween(mousePos, countryFlagSprite))
    { // Language
      /*pass
    }*/
    if (isClickBetween(mousePos, quitSprite))
    { // Quit
      /*pass*/
    }
  }

  void render(RenderWindow *pWindow)
  {
    pWindow->draw(this->menuBgSprite);
    pWindow->draw(this->btnSprite);
    pWindow->draw(this->settingsSprite);
    pWindow->draw(this->quitSprite);
    pWindow->draw(this->languageText);
    pWindow->draw(this->countryFlagSprite);

    // Title
    pWindow->draw(this->titleTextShadow);
    pWindow->draw(this->titleText);
    pWindow->draw(this->codersTextShadow);
    pWindow->draw(this->codersText);
  }
};