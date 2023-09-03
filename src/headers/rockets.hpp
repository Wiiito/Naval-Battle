#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace sf;

class Rocket {
private:
    int type;
    int orient;
    Sprite rocket[5];
    int spritePosX;
    std::vector<Vector2i> positions;
    std::vector<bool> hitsTaken;

public:
    Rocket(int type, int orient, Vector2i startPos);
    void makeRocketBody(Texture *texture, int textureOffset, Sprite *gameScreenReference, Vector2i boardOffset, int fs);
    bool didDestroy();
    bool hit(Vector2i pos);
    void draw(RenderWindow *pWindow);
    ~Rocket(){};
};
