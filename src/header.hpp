// Header archive
#pragma once  // To reduce build times to 1 only
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "lang/tinyxml2.cpp"
#include "lang/tinyxml2.h"

using namespace sf;

class Rocket {
   private:
    int type;
    int orient;
    Sprite rocket[5];
    void makeRocketBody();
    int spritePosX;

   public:
    Rocket(int type, int orient);
    void draw();
    ~Rocket(){};
};

class Player {
   private:
    /* data */

   public:
    Player(/* args */);
    ~Player();
};

RenderWindow window(VideoMode::getDesktopMode(), "Naval Battle", Style::Fullscreen /*Titlebar | Style::Close*/);
Event event;
Texture texture;
int textureOffset = 32;

int controlPanel = 4;
Player player;
Rocket rocket(4, 0);

// Window variables
Vector2u windowSize = window.getSize();
int windowWidth = windowSize.x;
int windowHeight = windowSize.y;

// This will be used so the code is more legible
int midWindowWidth = windowWidth / 2;
int midWindowHeight = windowHeight / 2;

// Declarando fontes
Font fontAnteb;
Font fontBlanka;
Font fontJedi;
Font fontMontserrat;

// Função criação texto
Text createText(String text, int posX, int posY, int textSize, Color color, String fontAtr = "Anteb", String locale = "left");

// Declarando coisinhas da minha lib
bool isClickBetween(Vector2i click, Sprite object);
// bool isClickBetween(Vector2i click, Text object);

// ---- Inicio Menu ----
// Declarando imagens Menu
Texture menuBgTx;
Sprite menuBgSprite;
// -- Texts --
// Coders
Text codersText;
Text codersTextShadow;

// Title
Text titleText;
Text titleTextShadow;

// Language Text
Text languageText;

// -- Botões --
// Start
Texture btnTx;
Sprite btnSprite;

// Configurações
Texture settingsTx;
Sprite settingsSprite;

// Bandeiras Paises
Texture countryFlagTx;
Sprite countryFlagSprite;

// Quit
Texture quitTx;
Sprite quitSprite;

// ---- Fim Menu ----

// ---- Inicio Language Settings ----
// Card linguagens / Backgound
Texture languageCardTx;
Sprite languageCardSprite;

Texture languageBackButtonTx;
Sprite languageBackButtonSprite;

// Idioma Text
Text languageTitleText;

Texture inUseTexture;
Sprite inDrawSprite;

// ---- XML Parser ----
// Declarando file para salva-la
tinyxml2::XMLDocument doc;

// Change language
std::string language;

// Changing lang on the xml
tinyxml2::XMLElement *pLastLang;

// Acesso a linguagens em todo o programa
tinyxml2::XMLElement *pLanguages;

std::vector<RectangleShape *> languageBackgrounds;

// Para não ter um conjunto absurdo de extrações pra cada linguagem,
// resolvi criar um array pra armazenas seus nomes
std::vector<Text *> languagesNames;

// ---- Fim Language Settings ----

void updateText();

// Game
int sizeBoardX = 10;
int sizeBoardY = 10;
int windowOffset = 32;

int *board = (int *)malloc(sizeof(int) * sizeBoardX * sizeBoardY);

int rockets[] = {4, 3, 2, 1};  // Barcos com 2,3,4,5 quadrado
int bombs = 50;

#include "lib/positions.cpp"
#include "lib/text.cpp"
