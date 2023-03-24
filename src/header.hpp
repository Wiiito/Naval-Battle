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

RenderWindow window(VideoMode(800, 600), "Naval Battle", Style::Titlebar | Style::Close);
Event event;
Player player;

// Declarando fontes
Font font;
Text createText(String text, int posX, int posY);

// Declarando coisinhas da minha lib
bool isClickBetween(Vector2i click, Vector2i iniPos, Vector2i finalPos);

// Mouse pos


#include "lib/positions.cpp"
#include "singleCall.cpp"
