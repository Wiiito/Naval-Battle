// Header archive
#pragma once  // To reduce build times to 1 only
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "lang/tinyxml2.cpp"
#include "lang/tinyxml2.h"

using namespace sf;

RenderWindow window(VideoMode::getDesktopMode(), "Naval Battle", Style::Fullscreen /*Titlebar | Style::Close*/);
Event event;
Texture texture;
Texture flagsTexture;

int flagsTextOffset = 64;
int textureOffset = 32;

int controlPanel = 4;

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
Sprite btnSprite;

// Configurações
Sprite settingsSprite;

// Bandeiras Paises
Sprite countryFlagSprite;

// Quit
Sprite quitSprite;

// ---- Fim Menu ----

// ---- Inicio Language Settings ----
// Card linguagens / Backgound
Texture languageCardTx;
Sprite languageCardSprite;

Sprite languageBackButtonSprite;

// Idioma Text
Text languageTitleText;

// Sprite e textura para bandeiras
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

void updateText();
// ---- Fim Language Settings ----

// ---- Inicio Game settings ----
// Strings (há textos que serão repeditos no jogo, declarando a string para não ter que extrair do xml 2x)
std::string settingsString;
std::string bombsString;
std::string gameMode;

// Textos a serem desenhados
Text settingsTitle;
Text bombsTextSettings;
Text boardText;
Text boardWidthText;
Text boardHeightText;
Text boatsText;
Text playerText;
Text twoBoatsTextTitle;
Text threeBoatsTextTitle;
Text fourBoatsTextTitle;
Text fiveBoatsTextTitle;

Sprite gameSinglePlayerSprite;
Sprite gameMultiPlayerSprite;
Sprite endScreenBackButton;
Sprite endScreenPlayAgain;

// Game Varibles
int sizeBoardX = 10;
int sizeBoardY = 10;
Vector2i windowOffset;

std::vector<int> boatsQuantity = {4, 3, 2, 1};
int bombsLeft;
int bombsNumber = 50;

// Just a reference to draw game objects (will not be draw)
Texture gameScreenReferenceTexture;
Sprite gameScreenReference;

// ---- Fim Game settings ----

// ---- Game Objects ----

// Casas do tabuleiro
Vector2i boardSize;
class Rocket {
   private:
    int type;
    int orient;
    Sprite rocket[5];
    void makeRocketBody();
    int spritePosX;
    std::vector<Vector2i> positions;
    std::vector<bool> hitsTaken;

   public:
    Rocket(int type, int orient, Vector2i startPos);
    bool didDestroy();
    bool hit(Vector2i pos);
    void draw();
    ~Rocket(){};
};

class Player {
   private:
    std::vector<Rocket *> rockets;
    void clearBoard();

   public:
    Player(/* args */);
    std::vector<std::vector<int>> board;
    void printBoard();
    int hit(Vector2i pos);
    ~Player();
};

class Bot {
   private:
    Vector2i randPos;
    bool destroying;
    Vector2f nextHit;
    // int difficulty;

   public:
    Bot();
    void getRandPos();
    void hitPos();
    ~Bot(){};
};
Bot bot;

std::vector<Player> Players;
int currentPlayer = 0;
bool restart = true;
// ---- End game Objects

// ---- Game render screen ----
Texture gameBackgroundTx;
Sprite gameBackgroundSprite;

Texture gamePlayersTx;
// ---- End game Objects

// ---- End screen ----
Text congratulationsText;
std::string wonString;

// ---- Mensagem perdeu ----
Text loseText;

// ---- Sound effects ----
Music musica;

SoundBuffer shootBuffer;
Sound shootSound;

SoundBuffer hitBuffer;
Sound hitSound;

SoundBuffer explodeBuffer;
Sound explodeSound;

#include "lib/positions.cpp"
#include "lib/text.cpp"
#include "players.cpp"
#include "rockets.cpp"