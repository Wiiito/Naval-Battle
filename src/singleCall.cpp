/*
  Aqui fica todas aquelas coisas que só precisam ser criadas uma unica vez, como por exemplo,
  funções de uso geral, declaração de variaveis utilizadas por todo o projeto, etc.
*/

#include <SFML/Graphics.hpp>

#include "header.hpp"

Text createText(String text, int posX, int posY) {
    Text startText;
    startText.setFont(font);
    startText.setString(text);
    startText.setCharacterSize(62);
    startText.setFillColor(Color::Black);
    startText.setStyle(Text::Bold);
    startText.setOrigin(startText.getLocalBounds().width / 2, 0 /*startText.getLocalBounds().height / 2*/);
    startText.setPosition(posX, posY);

    return startText;
}

