#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../headers/engine.hpp"
#include "../headers/players.hpp"
#include "../lang/tinyxml2.h"

using namespace sf;
using namespace std;

// Template for the game scenes
class SceneTemp
{
protected:
    int windowWidth;
    int windowHeight;

    Texture mainTexture;
    int textureOffset = 32;

    Texture menuBgTx;
    Sprite menuBgSprite;

    Sprite btnSprite;

    Sprite settingsSprite;

    Sprite quitSprite;

    Texture languageCardTx;
    Sprite languageCardSprite;

    Texture gameBackgroundTx;
    Sprite gameBackgroundSprite;

    Texture gameScreenReferenceTexture;
    Sprite gameScreenReference;

    Sprite gameSinglePlayerSprite;
    Sprite gameMultiPlayerSprite;

    Vector2i mousePos;

    // Declarando fontes
    Font fontAnteb;
    Font fontBlanka;
    Font fontJedi;
    Font fontMontserrat;

    // Declarando file para salva-la
    Text languageText;
    tinyxml2::XMLElement *pLanguage;
    string language;
    string languageToUpper;

    Texture flagsTexture;
    int flagsTextOffset = 64;
    Sprite countryFlagSprite;

    Text titleText;
    Text titleTextShadow;

    Text codersText;
    Text codersTextShadow;

    Text playerText;

    vector<RectangleShape *> languageBackgrounds;
    vector<Text *> languagesNames;

    int fs;

    Text createText(String text, int posX, int posY, int textSize, Color color, String fontAtr = "Anteb", String orientation = "left")
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

    void updateText()
    {
        // ---- Start Extracting Info from xml ----

        tinyxml2::XMLDocument doc;
        doc.LoadFile("src/lang/languages.xml");

        tinyxml2::XMLElement *pRootElement = doc.RootElement();
        tinyxml2::XMLElement *pLastLang = pRootElement->FirstChildElement("lastLang"); // Pegando a ultima lingua utilizada pelo usuario

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

        // std::cout << id << std::endl;

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
        Text languageTitleText = createText(languageStr, windowWidth / 2, windowWidth / 2 * 23 / 100, 4, Color::Black, "Blanka", "middle");

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
        string bombsString = selectedLang->FirstChildElement("bombs")->GetText();

        float leftBoarder = this->languageCardSprite.getGlobalBounds().left + 4 * fs;
        float topBoarder = windowWidth / 2 * 23 / 100 + 7 * fs;

        // Configurações
        Text settingsTitle = createText(settingsString, windowWidth / 2 + 2 * fs, windowWidth / 2 * 23 / 100, 4, Color::Black, "Blanka", "middle");
        // Bombas
        Text bombsTextSettings = createText(bombsString, leftBoarder, topBoarder, 3, Color::Black);

        // Esclusivos menu configurações

        // Tabuleiro
        Text boardText = createText(selectedLang->FirstChildElement("board")->GetText(), leftBoarder, topBoarder + 5 * fs, 3, Color::Black);
        // Largura
        Text boardWidthText = createText(selectedLang->FirstChildElement("width")->GetText(), leftBoarder + fs, topBoarder + 8 * fs, 3, Color::Black);
        // Altura
        Text boardHeightText = createText(selectedLang->FirstChildElement("height")->GetText(), leftBoarder + fs, topBoarder + 11 * fs, 3, Color::Black);
        // Barcos
        Text boatsText = createText(selectedLang->FirstChildElement("boats")->GetText(), leftBoarder, topBoarder + 15 * fs, 3, Color::Black);

        Text twoBoatsTextTitle = createText("2", leftBoarder + 1.5 * fs, topBoarder + 18 * fs, 3, Color::Black);
        Text threeBoatsTextTitle = createText("3", leftBoarder + 1.5 * fs, topBoarder + 20.5 * fs, 3, Color::Black);
        Text fourBoatsTextTitle = createText("4", leftBoarder + 1.5 * fs, topBoarder + 23 * fs, 3, Color::Black);
        Text fiveBoatsTextTitle = createText("5", leftBoarder + 1.5 * fs, topBoarder + 25.5 * fs, 3, Color::Black);

        // Player
        playerText = createText(
            selectedLang->FirstChildElement("player")->GetText(),
            gameScreenReference.getGlobalBounds().left + gameScreenReference.getLocalBounds().width * gameScreenReference.getScale().x / 2 - 2 * fs + 2 * fs,
            gameScreenReference.getGlobalBounds().top + 2 * fs,
            4,
            Color::Black
        );

        // ---- Fim Settings Menu ----

        // ---- Congratulations Start ----

        Text congratulationsText = createText(selectedLang->FirstChildElement("congratulations")->GetText(), windowWidth / 2,
                                              this->gameScreenReference.getGlobalBounds().top + 5 * fs, 8, Color::Black, "Blanka", "middle");
        string wonString = selectedLang->FirstChildElement("won")->GetText();

        // ---- Congratulations End ----

        // ---- Lose message Start ----

        Text loseText = createText(selectedLang->FirstChildElement("lose")->GetText(), windowWidth / 2,
                                   this->gameScreenReference.getGlobalBounds().top + 5 * fs, 8, Color::Black, "Blanka", "middle");

        // ---- Lose message End ----

        int control = 0; // Todas as linguas
        while (pLanguage)
        {
            // Colocando retangulos das linguagens a serem desenhadas dentro de um vector
            RectangleShape *shape = new RectangleShape;
            shape->setSize(Vector2f(this->languageCardSprite.getLocalBounds().width - 8 * fs, 4 * fs));
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

public:
    SceneTemp(){};
};

/*//  Language change card
    this->languageCardTx.loadFromFile("src/assets/languageCard.png");
    this->languageCardSprite.setTexture(this->languageCardTx);
    this->languageCardSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    this->languageCardSprite.setOrigin(this->languageCardSprite.getLocalBounds().width / 2, this->languageCardSprite.getLocalBounds().height / 2);
    this->languageCardSprite.setPosition(this->windowWidth / 2, this->windowHeight / 2);*/

/*s// Game Screen reference
this->gameScreenReferenceTexture.loadFromFile("src/assets/gameScreen.png");
this->gameScreenReference.setTexture(this->gameScreenReferenceTexture);
this->gameScreenReference.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
this->gameScreenReference.setOrigin(this->gameScreenReference.getLocalBounds().width / 2, this->gameScreenReference.getLocalBounds().height / 2);
this->gameScreenReference.setPosition(this->windowWidth / 2, this->windowHeight / 2);*/

// Fonte initialization
// fontAnteb.loadFromFile("src/assets/fonts/Anteb-Regular.ttf");
// fontBlanka.loadFromFile("src/assets/fonts/Blanka-Regular.otf");
// fontJedi.loadFromFile("src/assets/fonts/STARJEDI.TTF");
// fontMontserrat.loadFromFile("src/assets/fonts/Montserrat.OTF");