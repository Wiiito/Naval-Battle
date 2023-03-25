// Header archive
#pragma once  // To reduce build times to 1 only
#include <SFML/Graphics.hpp>

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
int controlPanel = 3;
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
Text createText(String text, int posX, int posY);

// Declarando coisinhas da minha lib
bool isClickBetween(Vector2i click, Vector2i iniPos, Vector2i finalPos);

// Mouse pos

#include "lib/positions.cpp"
#include "singleCall.cpp"
