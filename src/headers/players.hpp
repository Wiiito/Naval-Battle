#pragma once
#include "rockets.hpp"

using namespace sf;
using namespace std;

class Player {
private:
    vector<Rocket *> rockets;
    vector<int> boatsQuantity = {4, 3, 2, 1};

    Vector2i boardSizePx; // Tamanho do tabuleiro em pixels
    Vector2i squaresCount; // Quantidade de casas do tabuleiro no eixo Y
    Vector2i boardOffset; // Tamanho de cada casa do tabuleiro

    void clearBoard();

public:
    Player() {};
    Player(Vector2i boardSizePx, Vector2i squaresCount, Texture *texture, int textureOffset, Sprite *gameScreenReference, int fs);
    std::vector<std::vector<int>> board;
    void printBoard(RenderWindow *pWindow);
    int hit(Vector2i pos);
    ~Player();
};