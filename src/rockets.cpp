#include <cstdlib>
#include <iostream>

#include "header.hpp"

Rocket::Rocket(int type, int orient, Vector2i startPos) {
    this->type = type;
    this->orient = orient;

    // Setting positions to rocket
    for (int i = 0; i < type; i++) {
        positions.push_back(startPos + Vector2i(orient * i, !orient * i));
        hitsTaken.push_back(false);
    }

    makeRocketBody();
}

void Rocket::makeRocketBody() {
    for (int pos = 0; pos < type; pos++) {
        rocket[pos].setTexture(texture);
        rocket[pos].setPosition(sf::Vector2f(
            getInitialPos(gameScreenReference).x + 7 * fs + positions[pos].x * (boardSize.x / sizeBoardX),
            getInitialPos(gameScreenReference).y + 2 * fs + positions[pos].y * (boardSize.y / sizeBoardY) + (boardSize.y / sizeBoardY) * orient));

        rocket[pos].setRotation(-90 * orient);
        rocket[pos].setScale(Vector2f(
            (rocket[pos].getScale().x / textureOffset) * (windowOffset.x - 2) * !orient + (rocket[pos].getScale().y / textureOffset) * (windowOffset.y - 2) * orient,
            (rocket[pos].getScale().y / textureOffset) * (windowOffset.y - 2) * !orient + (rocket[pos].getScale().x / textureOffset) * (windowOffset.x - 2) * orient));

        if (type == 2) {
            spritePosX = textureOffset;
        } else {
            spritePosX = 0;
        }

        if (pos == 0) {
            rocket[pos].setTextureRect(sf::IntRect(spritePosX, textureOffset * 0, textureOffset, textureOffset));
        } else if (pos == type - 1 && type != 2) {
            rocket[pos].setTextureRect(sf::IntRect(spritePosX, textureOffset * 2, textureOffset, textureOffset));
        } else {
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

void Rocket::draw() {
    for (int pos = 0; pos < type; pos++) {
        if (hitsTaken[pos]) {
            window.draw(rocket[pos]);
        }
    }
}