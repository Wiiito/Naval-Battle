#include "headers/rockets.hpp"

using namespace sf;

Rocket::Rocket(int type, int orient, Vector2i startPos) {
    this->type = type;
    this->orient = orient;

    // Setting positions to rocket
    for (int i = 0; i < type; i++) {
        positions.push_back(startPos + Vector2i(orient * i, !orient * i));
        hitsTaken.push_back(false);
    }

}

/*
    Poderia ser feito no construtor,
    mas esse mundo de parametros somados com os do construtor
    ia ficar uma coisa tão grande quanto um codigo de 
    Hello World em Java \_(-_-)_/
*/
void Rocket::makeRocketBody(Texture *texture, int textureOffset, Sprite *gameScreenReference, Vector2i boardOffset, int fs) {
    for (int pos = 0; pos < type; pos++) { // Percorre cada parte do corpo do Foguete
        rocket[pos].setTexture(*texture); // Define a textura
        rocket[pos].setPosition(sf::Vector2f( // Define a posiçao na tela
            gameScreenReference->getGlobalBounds().left + 7 * fs + positions[pos].x * boardOffset.x,
            gameScreenReference->getGlobalBounds().top + 2 * fs + positions[pos].y * boardOffset.y + boardOffset.y * orient));

        rocket[pos].setRotation(-90 * orient); // Gira a parte atual do corpo em -90º caso orient == 1, para o corpo ficar na horizontal
        rocket[pos].setScale(Vector2f( // Seta a escala para a parte atual do corpo ser do mesmo tamanho exato da casa no tabuleiro
            (rocket[pos].getScale().x / textureOffset) * (boardOffset.x - 2) * !orient + (rocket[pos].getScale().y / textureOffset) * (boardOffset.y - 2) * orient,
            (rocket[pos].getScale().y / textureOffset) * (boardOffset.y - 2) * !orient + (rocket[pos].getScale().x / textureOffset) * (boardOffset.x - 2) * orient));

        if (type == 2) { // Para o foguete com dois quadrados te altura o sprite é diferente
            spritePosX = textureOffset;
        } else {
            spritePosX = 0;
        }

        if (pos == 0) { // Pega a parte de cima do foguete na textura
            rocket[pos].setTextureRect(sf::IntRect(spritePosX, textureOffset * 0, textureOffset, textureOffset));
        } else if (pos == type - 1 && type != 2) { // Pega a parte do meio do foguete na textura e repete qunatas vezes for necessário para completar o tamanho pedido para o foguete
            rocket[pos].setTextureRect(sf::IntRect(spritePosX, textureOffset * 2, textureOffset, textureOffset));
        } else { // Pega a parte de baixo do foguete na textura
            rocket[pos].setTextureRect(sf::IntRect(spritePosX, textureOffset * 1, textureOffset, textureOffset));
        }
    }
}

bool Rocket::didDestroy() {
    for (int i = 0; i < hitsTaken.size(); i++) {
        if (!hitsTaken[i]) {
            return false;
        }
    }
    return true;
}

bool Rocket::hit(Vector2i pos) {
    for (int i = 0; i < type; i++) {
        if (pos == positions[i]) {
            hitsTaken[i] = true;
            return true;
        }
    }
    return false;
}

void Rocket::draw(RenderWindow *pWindow) {
    for (int pos = 0; pos < type; pos++) {
        if (hitsTaken[pos]) {
            pWindow->draw(rocket[pos]);
        }
    }
}