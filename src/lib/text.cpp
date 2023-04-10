/*
  Aqui fica todas aquelas coisas que só precisam ser criadas uma unica vez, como por exemplo,
  funções de uso geral, declaração de variaveis utilizadas por todo o projeto, etc.
*/

#include <SFML/Graphics.hpp>

#include "../header.hpp"

// Fazendo um equivalente ao REM css (16px - 1080p)
int fs = (int)(windowHeight / 67.5);

// int buttonTextSize = (midWindowHeight - 80) / 3;  // 60 = 20 de espaçamento * 3 + 20 no final pra não ficar colado

Text createText(String text, int posX, int posY, int textSize, Color color, String fontAtr, String orientation) {
    Text startText;

    if (fontAtr == "Anteb") startText.setFont(fontAnteb);
    if (fontAtr == "Blanka") startText.setFont(fontBlanka);
    if (fontAtr == "Jedi") startText.setFont(fontJedi);
    if (fontAtr == "Montserrat") startText.setFont(fontMontserrat);

    startText.setString(text);
    startText.setCharacterSize(textSize * fs);
    startText.setFillColor(color);
    startText.setStyle(Text::Bold);
    if (orientation == "middle")
        startText.setOrigin(startText.getLocalBounds().width / 2, 0 /*startText.getLocalBounds().height / 2*/);
    if (orientation == "right")
        startText.setOrigin(startText.getLocalBounds().width, 0 /*startText.getLocalBounds().height / 2*/);

    startText.setPosition(posX, posY);

    return startText;
}

void drawValuesChanger(Vector2i mousePos, int *variable, Text text) {
    Vector2i textStart = getInitialPos(text);
    Vector2i textEnd = getFinalPos(text);

    Sprite upper;
    Sprite lower;

    upper.setTexture(texture);
    upper.setTextureRect(IntRect(2 * textureOffset, 2 * textureOffset, textureOffset, textureOffset));

    lower.setTexture(texture);
    lower.setTextureRect(IntRect(3 * textureOffset, 2 * textureOffset, textureOffset, textureOffset));

    upper.setScale((float)windowWidth * 0.5 / 1920, (float)windowHeight * 0.5 / 1080);
    upper.setOrigin(Vector2f(0, 0));
    upper.setPosition(textEnd.x + fs, textStart.y + fs);
    window.draw(upper);

    lower.setScale((float)windowWidth * 0.5 / 1920, (float)windowHeight * 0.5 / 1080);
    lower.setOrigin(Vector2f(0, 0));
    lower.setPosition(textEnd.x + fs, textEnd.y + 0.5 * fs);
    window.draw(lower);

    if (isClickBetween(mousePos, upper)) {
        (*variable)++;
    }
    if (isClickBetween(mousePos, lower)) {
        (*variable)--;
    }
}
