#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "../headers/engine.hpp"
#include "../headers/players.hpp"
#include "../lang/tinyxml2.h"

using namespace sf;
using namespace std;

// Template for the game scenes
class SceneTemp
{
protected:
    static int windowWidth;
    static int windowHeight;

    static Texture mainTexture;
    static int textureOffset;

    static Texture menuBgTx;
    static Sprite menuBgSprite;

    static Sprite btnSprite;

    static Sprite settingsSprite;

    static Sprite quitSprite;

    static Texture languageCardTx;
    static Sprite languageCardSprite;

    static Texture gameBackgroundTx;
    static Sprite gameBackgroundSprite;

    static Texture gameScreenReferenceTexture;
    static Sprite gameScreenReference;

    static Sprite gameSinglePlayerSprite;
    static Sprite gameMultiPlayerSprite;

    static Sprite languageBackButtonSprite;

    static Sprite endScreenBackButton;
    static Sprite endScreenPlayAgain;

    static Vector2i mousePos;

    // Declarando fontes
    static Font fontAnteb;
    static Font fontBlanka;
    static Font fontJedi;
    static Font fontMontserrat;

    // Declarando file para salva-la
    static tinyxml2::XMLDocument doc;
    static Text languageText;
    static tinyxml2::XMLElement *pLanguage;
    static tinyxml2::XMLElement *pLastLang;
    static string language;
    static string languageToUpper;

    static string bombsString;

    static Texture flagsTexture;
    static int flagsTextOffset;
    static Sprite countryFlagSprite;

    // Sprite e textura para bandeiras
    static Texture inUseTexture;
    static Sprite inDrawSprite;

    static Text titleText;
    static Text titleTextShadow;
    static Text languageTitleText;

    static Text codersText;
    static Text codersTextShadow;
    static Text bombsTextSettings;
    static Text boardWidthText;
    static Text boardHeightText;

    static Text twoBoatsTextTitle;
    static Text threeBoatsTextTitle;
    static Text fourBoatsTextTitle;
    static Text fiveBoatsTextTitle;
    static Text settingsTitle;

    static Text playerText;
    static Text congratulationsText;
    static string wonString;
    static string loseString;

    // ---- Sound effects ----
    static Music musica;

    static SoundBuffer shootBuffer;
    static Sound shootSound;

    static SoundBuffer hitBuffer;
    static Sound hitSound;

    static SoundBuffer explodeBuffer;
    static Sound explodeSound;

    static vector<RectangleShape *> languageBackgrounds;
    static vector<Text *> languagesNames;

    static int fs;
    static int currentPlayer;

    // Settings variaables
    static int bombsNumber;
    static string gameMode;
    static Vector2i boardSizePx;
    static Vector2i squaresCount;
    static vector<int> boatsQuantity;
    static Text boardText;
    static Text boatsText;

    static float leftBoarder;
    static float topBoarder;
    static bool win;

    static Text createText(String text, int posX, int posY, int textSize, Color color, String fontAtr = "Anteb", String orientation = "left")
    {
        Text startText;

        if (fontAtr == "Anteb")
            startText.setFont(fontAnteb);
        if (fontAtr == "Blanka")
            startText.setFont(fontBlanka);
        if (fontAtr == "Jedi")
            startText.setFont(fontJedi);
        if (fontAtr == "Montserrat")
            startText.setFont(fontMontserrat);

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

    static void updateText()
    {
        // ---- Start Extracting Info from xml ----

        doc.LoadFile("src/lang/languages.xml");

        tinyxml2::XMLElement *pRootElement = doc.RootElement();
        pLastLang = pRootElement->FirstChildElement("lastLang"); // Pegando a ultima lingua utilizada pelo usuario

        string codersStr = pRootElement->FirstChildElement("coders")->GetText();

        tinyxml2::XMLElement *pLanguages = pRootElement->FirstChildElement("languages");
        tinyxml2::XMLElement *selectedLang = pLanguages->FirstChildElement(pLastLang->GetText());

        // Saving pointers to string
        string language = pLanguages->FirstChildElement(pLastLang->GetText())->FirstChildElement("acronym")->GetText();

        String titleStr = selectedLang->FirstChildElement("title")->GetText();
        String nameStr = selectedLang->FirstChildElement("name")->GetText();
        int id;
        selectedLang->QueryAttribute("id", &id);
        String languageStr = selectedLang->FirstChildElement("language")->GetText();

        // ---- End Extracting Info from xml ----

        // ---- Generating Menu texts ----
        // Title
        if (language == "en")
        {
            titleTextShadow = createText(titleStr, windowWidth * 45 / 100 + 4, windowHeight * 10 / 100 + 4, 8, Color::Black, "Jedi", "middle");
            titleText = createText(titleStr, windowWidth * 45 / 100, windowHeight * 10 / 100, 8, Color::White, "Jedi", "middle");
        }
        else
        {
            titleTextShadow = createText(titleStr, windowWidth * 45 / 100 + 4, windowHeight * 10 / 100 + 4, 8, Color::Black, "Blanka", "middle");
            titleText = createText(titleStr, windowWidth * 45 / 100, windowHeight * 10 / 100, 8, Color::White, "Blanka", "middle");
        }

        // Coders
        codersTextShadow = createText(codersStr, windowWidth * 45 / 100 + 2, windowHeight * 23 / 100 + 2, 2, Color::Black, "Anteb", "middle");
        codersText = createText(codersStr, windowWidth * 45 / 100, windowHeight * 23 / 100, 2, Color::White, "Anteb", "middle");

        // Language
        languageToUpper = language; // Não to mudando a language porquê ela vai ser usada pra mudar a linguagem em lowerCase
        for (int i = 0; i < language.size(); i++)
        {
            languageToUpper[i] = toupper(language[i]);
        }
        languageText = createText(languageToUpper, windowWidth * 95 / 100, windowHeight * 3 / 100, 2, Color::White, "Montserrat", "Right");

        // Language Title Text
        languageTitleText = createText(languageStr, windowWidth / 2, windowWidth / 2 * 23 / 100, 4, Color::Black, "Blanka", "middle");

        // ---- End Menu Texts Generation ----

        // ---- Bandeira em uso ----
        // Colocando a bandeira aqui pra ela atualizar assim que a linguagem mudar

        countryFlagSprite.setTexture(flagsTexture);
        countryFlagSprite.setTextureRect(IntRect(id * flagsTextOffset, 0, flagsTextOffset, flagsTextOffset));
        countryFlagSprite.setScale((float)windowWidth * 0.8 / 1920, (float)windowHeight * 0.8 / 1080);
        countryFlagSprite.setOrigin(countryFlagSprite.getLocalBounds().width, 0);
        countryFlagSprite.setPosition(languageText.getGlobalBounds().left, languageText.getGlobalBounds().top - 10);

        // ---- Fim bandeira em uso ----

        // ---- Language Backgrounds ----
        pLanguage = pLanguages->FirstChildElement();

        // Limpando memoria pra evitar leaks
        for (int i = 0; i < languagesNames.size(); i++)
        {
            delete languageBackgrounds[i];
            delete languagesNames[i];
        }

        languageBackgrounds.clear(); // Limpando o vector quando muda a lingua
        languagesNames.clear();      // Limpando linguagens pra não duplicar elas

        // Diminuido o tamanho dos vetores pra evitar probmelas com .push_back()
        languageBackgrounds.shrink_to_fit();
        languagesNames.shrink_to_fit();

        // ---- Inicio Settings Menu ----
        string settingsString = selectedLang->FirstChildElement("settings")->GetText();
        bombsString = selectedLang->FirstChildElement("bombs")->GetText();

        leftBoarder = languageCardSprite.getGlobalBounds().left + 4 * fs;
        topBoarder = windowWidth / 2 * 23 / 100 + 7 * fs;

        // Configurações
        settingsTitle = createText(settingsString, windowWidth / 2 + 2 * fs, windowWidth / 2 * 23 / 100, 4, Color::Black, "Blanka", "middle");
        // Bombas
        bombsTextSettings = createText(bombsString, leftBoarder, topBoarder, 3, Color::Black);

        // Esclusivos menu configurações

        // Tabuleiro
        boardText = createText(selectedLang->FirstChildElement("board")->GetText(), leftBoarder, topBoarder + 5 * fs, 3, Color::Black);
        // Largura
        boardWidthText = createText(selectedLang->FirstChildElement("width")->GetText(), leftBoarder + fs, topBoarder + 8 * fs, 3, Color::Black);
        // Altura
        boardHeightText = createText(selectedLang->FirstChildElement("height")->GetText(), leftBoarder + fs, topBoarder + 11 * fs, 3, Color::Black);
        // Barcos
        boatsText = createText(selectedLang->FirstChildElement("boats")->GetText(), leftBoarder, topBoarder + 15 * fs, 3, Color::Black);

        twoBoatsTextTitle = createText("2", leftBoarder + 1.5 * fs, topBoarder + 18 * fs, 3, Color::Black);
        threeBoatsTextTitle = createText("3", leftBoarder + 1.5 * fs, topBoarder + 20.5 * fs, 3, Color::Black);
        fourBoatsTextTitle = createText("4", leftBoarder + 1.5 * fs, topBoarder + 23 * fs, 3, Color::Black);
        fiveBoatsTextTitle = createText("5", leftBoarder + 1.5 * fs, topBoarder + 25.5 * fs, 3, Color::Black);

        // Player
        playerText = createText(selectedLang->FirstChildElement("player")->GetText(),
                                gameScreenReference.getGlobalBounds().left + 7 * fs + gameScreenReference.getLocalBounds().width * gameScreenReference.getScale().x / 2 - 2 * fs + 2 * fs,
                                gameScreenReference.getGlobalBounds().top + 2 * fs,
                                4,
                                Color::Black);

        // ---- Fim Settings Menu ----

        // ---- Congratulations Start ----

        congratulationsText = createText(selectedLang->FirstChildElement("congratulations")->GetText(), windowWidth / 2,
                                         gameScreenReference.getGlobalBounds().top + 5 * fs, 8, Color::Black, "Blanka", "middle");
        wonString = selectedLang->FirstChildElement("won")->GetText();

        // ---- Congratulations End ----

        // ---- Lose message Start ----

        loseString = selectedLang->FirstChildElement("lose")->GetText();

        // Text loseText = createText(selectedLang->FirstChildElement("lose")->GetText(), windowWidth / 2,
        //                           gameScreenReference.getGlobalBounds().top + 5 * fs, 8, Color::Black, "Blanka", "middle");

        // ---- Lose message End ----

        int control = 0; // Todas as linguas
        while (pLanguage)
        {
            // Colocando retangulos das linguagens a serem desenhadas dentro de um vector
            RectangleShape *shape = new RectangleShape;
            shape->setSize(Vector2f(languageCardSprite.getLocalBounds().width - 8 * fs, 4 * fs));
            shape->setScale((float)windowWidth / 1920, 1);
            shape->setOrigin(shape->getLocalBounds().width / 2, 0);
            shape->setPosition(windowWidth / 2, (float)windowHeight * 320 / 1080 + 5 * fs * control);

            // Mudando a opacidade da linguagem em uso
            if (nameStr == pLanguage->FirstChildElement("name")->GetText())
            {
                shape->setFillColor(Color(255, 255, 255, 200));
            }
            else
            {
                shape->setFillColor(Color(255, 255, 255, 100));
            }

            // Array de textos
            Text *langText = new Text;
            *langText = createText(pLanguage->FirstChildElement("name")->GetText(),
                                   shape->getPosition().x + shape->getLocalBounds().width * shape->getScale().x / 2 - 2 * fs,
                                   shape->getPosition().y, 3, Color::Black, "Anteb", "right");

            // Adicionando aos vetores
            languageBackgrounds.push_back(shape);
            languagesNames.push_back(langText);

            // Passando para a proxima lingua
            pLanguage = pLanguage->NextSiblingElement();
            control++;
        }
    }

    bool isClickBetween(Vector2i click, Sprite object)
    {
        Vector2f iniPos = {object.getGlobalBounds().left, object.getGlobalBounds().top};
        Vector2f finalPos = {object.getGlobalBounds().left + object.getGlobalBounds().width, object.getGlobalBounds().top + object.getGlobalBounds().height};
        if (click.x >= iniPos.x && click.y >= iniPos.y && click.x <= finalPos.x && click.y <= finalPos.y)
        {
            return true;
        }
        return false;
    }

    bool isClickBetween(Vector2i click, RectangleShape object)
    {
        Vector2f iniPos = {object.getGlobalBounds().left, object.getGlobalBounds().top};
        Vector2f finalPos = {object.getGlobalBounds().left + object.getGlobalBounds().width, object.getGlobalBounds().top + object.getGlobalBounds().height};
        if (click.x >= iniPos.x && click.y >= iniPos.y && click.x <= finalPos.x && click.y <= finalPos.y)
        {
            return true;
        }
        return false;
    }

    bool isClickBetween(Vector2i click, Text object)
    {
        Vector2f iniPos = {object.getGlobalBounds().left, object.getGlobalBounds().top};
        Vector2f finalPos = {object.getGlobalBounds().left + object.getGlobalBounds().width, object.getGlobalBounds().top + object.getGlobalBounds().height};
        if (click.x >= iniPos.x && click.y >= iniPos.y && click.x <= finalPos.x && click.y <= finalPos.y)
        {
            return true;
        }
        return false;
    }

public:
    SceneTemp(){};

    static void defTextures(Vector2u windowSize)
    {
        // Window variables
        windowWidth = windowSize.x;
        windowHeight = windowSize.y;

        // Creating a scale to font size (16px - 1080p)
        fs = (int)(windowHeight / 67.5);

        textureOffset = 32;
        flagsTextOffset = 64;

        musica.openFromFile("src/assets/sounds/Hardmoon_-_Deep_space.ogg");
        musica.setVolume(65.f);
        musica.setLoop(true);
        musica.play();

        shootBuffer.loadFromFile("src/assets/sounds/shoot.ogg");
        shootSound.setBuffer(shootBuffer);

        hitBuffer.loadFromFile("src/assets/sounds/hitSound.flac");
        hitSound.setBuffer(hitBuffer);

        explodeBuffer.loadFromFile("src/assets/sounds/explosionSound.flac");
        explodeSound.setBuffer(explodeBuffer);

        // Game Main Texture
        mainTexture.loadFromFile("src/assets/sprites.png");

        // Flags texture
        flagsTexture.loadFromFile("src/assets/flags.png");

        // Fonte initialization
        fontAnteb.loadFromFile("src/assets/fonts/Anteb-Regular.ttf");
        fontBlanka.loadFromFile("src/assets/fonts/Blanka-Regular.otf");
        fontMontserrat.loadFromFile("src/assets/fonts/Montserrat.OTF");
        fontJedi.loadFromFile("src/assets/fonts/STARJEDI.TTF");

        // Background
        menuBgTx.loadFromFile("src/assets/menuBackground.png");
        menuBgSprite.setTexture(menuBgTx);
        menuBgSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        menuBgSprite.setOrigin(menuBgSprite.getLocalBounds().width / 2, menuBgSprite.getLocalBounds().height / 2);
        menuBgSprite.setPosition(windowWidth / 2, windowHeight / 2);

        // Start Button
        btnSprite.setTexture(mainTexture);
        btnSprite.setTextureRect(IntRect(0, 3 * textureOffset, 9 * textureOffset, 3 * textureOffset));
        btnSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        btnSprite.setOrigin(btnSprite.getLocalBounds().width / 2, btnSprite.getLocalBounds().height / 2);
        btnSprite.setPosition(windowWidth * 50 / 100, windowHeight * 78 / 100);

        // Settings Button
        settingsSprite.setTexture(mainTexture);
        settingsSprite.setTextureRect(IntRect(4 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
        settingsSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        settingsSprite.setOrigin(0, settingsSprite.getLocalBounds().height);
        settingsSprite.setPosition(windowWidth * 2 / 100, windowHeight * 96 / 100);

        // Quit Button
        quitSprite.setTexture(mainTexture);
        quitSprite.setTextureRect(IntRect(6 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
        quitSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        quitSprite.setOrigin(quitSprite.getLocalBounds().width, quitSprite.getLocalBounds().height);
        quitSprite.setPosition(windowWidth * 98 / 100, windowHeight * 96 / 100);

        gameSinglePlayerSprite.setTexture(mainTexture);
        gameSinglePlayerSprite.setTextureRect(IntRect(0, 6 * textureOffset, 13 * textureOffset, 13 * textureOffset));
        gameSinglePlayerSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        gameSinglePlayerSprite.setOrigin(gameSinglePlayerSprite.getLocalBounds().width / 2, gameSinglePlayerSprite.getLocalBounds().height / 2);
        gameSinglePlayerSprite.setPosition(windowWidth * 1 / 3, windowHeight / 2);

        gameMultiPlayerSprite.setTexture(mainTexture);
        gameMultiPlayerSprite.setTextureRect(IntRect(13 * textureOffset, 6 * textureOffset, 13 * textureOffset, 13 * textureOffset));
        gameMultiPlayerSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        gameMultiPlayerSprite.setOrigin(gameMultiPlayerSprite.getLocalBounds().width / 2, gameMultiPlayerSprite.getLocalBounds().height / 2);
        gameMultiPlayerSprite.setPosition(windowWidth * 2 / 3, windowHeight / 2);

        // ---- Game background ----
        gameBackgroundTx.loadFromFile("src/assets/gameBackground.png");
        gameBackgroundSprite.setTexture(gameBackgroundTx);
        gameBackgroundSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        gameBackgroundSprite.setOrigin(gameBackgroundSprite.getLocalBounds().width / 2, gameBackgroundSprite.getLocalBounds().height / 2);
        gameBackgroundSprite.setPosition(windowWidth / 2, windowHeight / 2);

        // Game Screen reference
        gameScreenReferenceTexture.loadFromFile("src/assets/gameScreen.png");
        gameScreenReference.setTexture(gameScreenReferenceTexture);
        gameScreenReference.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        gameScreenReference.setOrigin(gameScreenReference.getLocalBounds().width / 2, gameScreenReference.getLocalBounds().height / 2);
        gameScreenReference.setPosition(windowWidth / 2, windowHeight / 2);

        //  Language change card
        languageCardTx.loadFromFile("src/assets/languageCard.png");
        languageCardSprite.setTexture(languageCardTx);
        languageCardSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        languageCardSprite.setOrigin(languageCardSprite.getLocalBounds().width / 2, languageCardSprite.getLocalBounds().height / 2);
        languageCardSprite.setPosition(windowWidth / 2, windowHeight / 2);

        // Language Back Button
        languageBackButtonSprite.setTexture(mainTexture);
        languageBackButtonSprite.setTextureRect(IntRect(2 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
        languageBackButtonSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
        languageBackButtonSprite.setOrigin(languageBackButtonSprite.getLocalBounds().width / 2, languageBackButtonSprite.getLocalBounds().height / 2);
        languageBackButtonSprite.setPosition(windowWidth * 33 / 100, windowHeight * 8 / 10);

        // Win screen back button
        endScreenBackButton.setTexture(mainTexture);
        endScreenBackButton.setTextureRect(IntRect(10 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
        endScreenBackButton.setScale((float)windowWidth * 1.6 / 1920, (float)windowHeight * 1.6 / 1080);
        endScreenBackButton.setOrigin(endScreenBackButton.getLocalBounds().width / 2, endScreenBackButton.getLocalBounds().height / 2);
        endScreenBackButton.setPosition(windowWidth / 2 + 10 * fs, (windowHeight / 2) + (windowHeight / 2) * 1.3 / 5);

        // Win play again button
        endScreenPlayAgain.setTexture(mainTexture);
        endScreenPlayAgain.setTextureRect(IntRect(8 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
        endScreenPlayAgain.setScale((float)windowWidth * 1.6 / 1920, (float)windowHeight * 1.6 / 1080);
        endScreenPlayAgain.setOrigin(endScreenPlayAgain.getLocalBounds().width / 2, endScreenPlayAgain.getLocalBounds().height / 2);
        endScreenPlayAgain.setPosition(windowWidth / 2 - 10 * fs, (windowHeight / 2) + (windowHeight / 2) * 1.3 / 5);

        // Calculando o tamanho maximo do tabuleiro
        boardSizePx = Vector2i(gameScreenReference.getLocalBounds().width * gameScreenReference.getScale().x / 2 - 2 * fs,
                               gameScreenReference.getLocalBounds().height * gameScreenReference.getScale().y - 4 * fs);

        // Standard Settings
        bombsNumber = 50;
        squaresCount = {10, 10};
        boatsQuantity = {4, 3, 2, 1};

        updateText();
    };
};

int SceneTemp::windowWidth;
int SceneTemp::windowHeight;

Texture SceneTemp::mainTexture;
int SceneTemp::textureOffset;

Texture SceneTemp::menuBgTx;
Sprite SceneTemp::menuBgSprite;

Sprite SceneTemp::btnSprite;

Sprite SceneTemp::settingsSprite;

Sprite SceneTemp::quitSprite;

Texture SceneTemp::languageCardTx;
Sprite SceneTemp::languageCardSprite;

Texture SceneTemp::gameBackgroundTx;
Sprite SceneTemp::gameBackgroundSprite;

Texture SceneTemp::gameScreenReferenceTexture;
Sprite SceneTemp::gameScreenReference;

Sprite SceneTemp::gameSinglePlayerSprite;
Sprite SceneTemp::gameMultiPlayerSprite;

Sprite SceneTemp::languageBackButtonSprite;

Sprite SceneTemp::endScreenBackButton;
Sprite SceneTemp::endScreenPlayAgain;

Vector2i SceneTemp::mousePos;

Font SceneTemp::fontAnteb;
Font SceneTemp::fontBlanka;
Font SceneTemp::fontJedi;
Font SceneTemp::fontMontserrat;

tinyxml2::XMLDocument SceneTemp::doc;
Text SceneTemp::languageText;
tinyxml2::XMLElement *SceneTemp::pLanguage;
tinyxml2::XMLElement *SceneTemp::pLastLang;
string SceneTemp::language;
string SceneTemp::languageToUpper;

string SceneTemp::bombsString;

Texture SceneTemp::flagsTexture;
int SceneTemp::flagsTextOffset;
Sprite SceneTemp::countryFlagSprite;

Texture SceneTemp::inUseTexture;
Sprite SceneTemp::inDrawSprite;

Text SceneTemp::titleText;
Text SceneTemp::titleTextShadow;
Text SceneTemp::languageTitleText;

Text SceneTemp::codersText;
Text SceneTemp::codersTextShadow;
Text SceneTemp::bombsTextSettings;
Text SceneTemp::boardWidthText;
Text SceneTemp::boardHeightText;

Text SceneTemp::twoBoatsTextTitle;
Text SceneTemp::threeBoatsTextTitle;
Text SceneTemp::fourBoatsTextTitle;
Text SceneTemp::fiveBoatsTextTitle;
Text SceneTemp::settingsTitle;

Text SceneTemp::playerText;
Text SceneTemp::congratulationsText;
string SceneTemp::wonString;
string SceneTemp::loseString;

Music SceneTemp::musica;

SoundBuffer SceneTemp::shootBuffer;
Sound SceneTemp::shootSound;

SoundBuffer SceneTemp::hitBuffer;
Sound SceneTemp::hitSound;

SoundBuffer SceneTemp::explodeBuffer;
Sound SceneTemp::explodeSound;

vector<RectangleShape *> SceneTemp::languageBackgrounds;
vector<Text *> SceneTemp::languagesNames;

int SceneTemp::fs;
int SceneTemp::currentPlayer;

int SceneTemp::bombsNumber;
string SceneTemp::gameMode;
Vector2i SceneTemp::boardSizePx;
Vector2i SceneTemp::squaresCount;
vector<int> SceneTemp::boatsQuantity;
Text SceneTemp::boardText;
Text SceneTemp::boatsText;

float SceneTemp::leftBoarder;
float SceneTemp::topBoarder;
bool SceneTemp::win;
