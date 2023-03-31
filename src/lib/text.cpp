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

void drawArrowValues(Vector2i mousePos, int *variable, Text text) {
    /*Vector2i textEnd(getFinalPos(text).x, getFinalPos(text).y - text.getLocalBounds().height);

    // Criando a sete de cima
    Text upArrow = createText("<", textEnd.x, textEnd.y, text.getCharacterSize() / 1.5);

    upArrow.setOrigin(upArrow.getLocalBounds().width, upArrow.getLocalBounds().height);
    upArrow.move(upArrow.getLocalBounds().height * 1.25, upArrow.getLocalBounds().width * 1.9);
    upArrow.setRotation(90.f);

    Text downArrow = createText(">", textEnd.x, textEnd.y, text.getCharacterSize() / 1.5);

    downArrow.setOrigin(downArrow.getLocalBounds().width, downArrow.getLocalBounds().height);
    downArrow.move(downArrow.getLocalBounds().height * 1.25, downArrow.getLocalBounds().width * 3.25);
    downArrow.setRotation(90.f);

    if (isClickBetween(mousePos, upArrow)) {
        (*variable)++;
    }
    if (isClickBetween(mousePos, downArrow)) {
        (*variable)--;
    }

    window.draw(upArrow);
    window.draw(downArrow);*/
}

// String getText(string text) {
// }