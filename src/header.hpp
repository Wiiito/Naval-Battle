// Header archive
#pragma once  // To reduce build times to 1 only
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Boat {
   private:
    /* data */

   public:
    Boat(/* args */);
    ~Boat();
};

class Player {
   private:
    /* data */

   public:
    Player(/* args */);
    ~Player();
};

RenderWindow window(VideoMode::getDesktopMode(), "Naval Battle", Style::Fullscreen /*Titlebar | Style::Close*/);
int controlPanel = 4;
Event event;
Player player;

// Window variables
Vector2u windowSize = window.getSize();
int windowWidth = windowSize.x;
int windowHeight = windowSize.y;

// This will be used so the code is more legible
int midWindowWidth = windowWidth / 2;
int midWindowHeight = windowHeight / 2;

// Declarando fontes
Font font;
Text createText(String text, int posX, int posY, int textSize, String locale = "left");

// Declarando coisinhas da minha lib
bool isClickBetween(Vector2i click, Sprite object);

// ---- Inicio Menu ----
// Declarando imagens Menu
Texture menuBgTx;
Sprite menuBgSprite;

// Botão
Texture btnTx;
Sprite btnSprite;

// ---- Fim Menu ----

// Game
int sizeBoardX = 10;
int sizeBoardY = 10;

int *board = (int *)malloc(sizeof(int) * sizeBoardX * sizeBoardY);

int boats[] = {4, 3, 2, 1};  // Barcos com 2,3,4,5 quadrados
int bombs = 50;

#include "lib/positions.cpp"
#include "lib/text.cpp"
