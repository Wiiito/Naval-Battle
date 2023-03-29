#include "header.hpp"

// Variables that need yo be initialized only one time will be here

void initializeVar() {
    //  Menu Background
    menuBgTx.loadFromFile("src/assets/menuBackground.png");
    menuBgSprite.setTexture(menuBgTx);
    menuBgSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    menuBgSprite.setOrigin(menuBgSprite.getLocalBounds().width / 2, menuBgSprite.getLocalBounds().height / 2);
    menuBgSprite.setPosition(midWindowWidth, midWindowHeight);

    //  Menu Start Button
    btnTx.loadFromFile("src/assets/startButton.png");
    btnSprite.setTexture(btnTx);
    btnSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    btnSprite.setOrigin(btnSprite.getLocalBounds().width / 2, btnSprite.getLocalBounds().height / 2);
    btnSprite.setPosition(midWindowWidth * 90 / 100, windowHeight * 78 / 100);
}