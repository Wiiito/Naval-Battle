#include <time.h>

#include <iostream>

#include "header.hpp"

// Variables that need to be initialized only one time will be here

void initializeVar() {
    srand(time(NULL));  // Randomize rand() value

    // Game texture
    texture.loadFromFile("src/assets/sprites.png");

    // Flags texture
    flagsTexture.loadFromFile("src/assets/flags.png");

    // Fonte initialization
    fontAnteb.loadFromFile("src/assets/fonts/Anteb-Regular.ttf");
    fontBlanka.loadFromFile("src/assets/fonts/Blanka-Regular.otf");
    fontJedi.loadFromFile("src/assets/fonts/STARJEDI.TTF");
    fontMontserrat.loadFromFile("src/assets/fonts/Montserrat.OTF");

    //  Menu Background
    menuBgTx.loadFromFile("src/assets/menuBackground.png");
    menuBgSprite.setTexture(menuBgTx);
    menuBgSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    menuBgSprite.setOrigin(menuBgSprite.getLocalBounds().width / 2, menuBgSprite.getLocalBounds().height / 2);
    menuBgSprite.setPosition(midWindowWidth, midWindowHeight);

    //  Menu Start Button
    btnSprite.setTexture(texture);
    btnSprite.setTextureRect(IntRect(0, 3 * textureOffset, 9 * textureOffset, 3 * textureOffset));
    btnSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    btnSprite.setOrigin(btnSprite.getLocalBounds().width / 2, btnSprite.getLocalBounds().height / 2);
    btnSprite.setPosition(midWindowWidth * 90 / 100, windowHeight * 78 / 100);

    //  Menu Settings Button
    settingsSprite.setTexture(texture);
    settingsSprite.setTextureRect(IntRect(4 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
    settingsSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    settingsSprite.setOrigin(0, settingsSprite.getLocalBounds().height);
    settingsSprite.setPosition(windowWidth * 2 / 100, windowHeight * 96 / 100);

    //  Menu Settings Button
    quitSprite.setTexture(texture);
    quitSprite.setTextureRect(IntRect(6 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
    quitSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    quitSprite.setOrigin(quitSprite.getLocalBounds().width, quitSprite.getLocalBounds().height);
    quitSprite.setPosition(windowWidth * 98 / 100, windowHeight * 96 / 100);

    //  Language change card
    languageCardTx.loadFromFile("src/assets/languageCard.png");
    languageCardSprite.setTexture(languageCardTx);
    languageCardSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    languageCardSprite.setOrigin(languageCardSprite.getLocalBounds().width / 2, languageCardSprite.getLocalBounds().height / 2);
    languageCardSprite.setPosition(midWindowWidth, midWindowHeight);

    // Language Settings base sprite
    inDrawSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    inDrawSprite.setOrigin(inDrawSprite.getLocalBounds().width / 2, inDrawSprite.getLocalBounds().height / 2);

    // Language Back Button
    languageBackButtonSprite.setTexture(texture);
    languageBackButtonSprite.setTextureRect(IntRect(2 * textureOffset, 0, 2 * textureOffset, 2 * textureOffset));
    languageBackButtonSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    languageBackButtonSprite.setOrigin(languageBackButtonSprite.getLocalBounds().width / 2, languageBackButtonSprite.getLocalBounds().height / 2);
    languageBackButtonSprite.setPosition(windowWidth * 33 / 100, windowHeight * 8 / 10);

    // ---- Game render ----
    gameBackgroundTx.loadFromFile("src/assets/gameBackground.png");
    gameBackgroundSprite.setTexture(gameBackgroundTx);
    gameBackgroundSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    gameBackgroundSprite.setOrigin(gameBackgroundSprite.getLocalBounds().width / 2, gameBackgroundSprite.getLocalBounds().height / 2);
    gameBackgroundSprite.setPosition(midWindowWidth, midWindowHeight);

    gamePlayersTx.loadFromFile("src/assets/players.png");

    gameSinglePlayerSprite.setTexture(gamePlayersTx);
    gameSinglePlayerSprite.setTextureRect(IntRect(0, 0, 402, 402));
    gameSinglePlayerSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    gameSinglePlayerSprite.setOrigin(gameSinglePlayerSprite.getLocalBounds().width / 2, gameSinglePlayerSprite.getLocalBounds().height / 2);
    gameSinglePlayerSprite.setPosition(windowWidth * 1 / 3, midWindowHeight);

    gameMultiPlayerSprite.setTexture(gamePlayersTx);
    gameMultiPlayerSprite.setTextureRect(IntRect(402, 0, 402, 402));
    gameMultiPlayerSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    gameMultiPlayerSprite.setOrigin(gameMultiPlayerSprite.getLocalBounds().width / 2, gameMultiPlayerSprite.getLocalBounds().height / 2);
    gameMultiPlayerSprite.setPosition(windowWidth * 2 / 3, midWindowHeight);

    // Game Screen reference
    gameScreenReferenceTexture.loadFromFile("src/assets/gameScreen.png");
    gameScreenReference.setTexture(gameScreenReferenceTexture);
    gameScreenReference.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    gameScreenReference.setOrigin(gameScreenReference.getLocalBounds().width / 2, gameScreenReference.getLocalBounds().height / 2);
    gameScreenReference.setPosition(midWindowWidth, midWindowHeight);

    updateText();  // First generation of the text
}

void updateText() {
    // ---- Start Extracting Info from xml ----

    doc.LoadFile("src/lang/languages.xml");

    tinyxml2::XMLElement *pRootElement = doc.RootElement();
    pLastLang = pRootElement->FirstChildElement("lastLang");  // Pegando a ultima lingua utilizada pelo usuario

    std::string codersStr = pRootElement->FirstChildElement("coders")->GetText();

    pLanguages = pRootElement->FirstChildElement("languages");
    tinyxml2::XMLElement *selectedLang = pLanguages->FirstChildElement(pLastLang->GetText());

    // Saving pointers to string
    language = pLanguages->FirstChildElement(pLastLang->GetText())->FirstChildElement("acronym")->GetText();

    String titleStr = selectedLang->FirstChildElement("title")->GetText();
    String nameStr = selectedLang->FirstChildElement("name")->GetText();
    int id;
    selectedLang->QueryAttribute("id", &id);
    String languageStr = selectedLang->FirstChildElement("language")->GetText();

    // std::cout << id << std::endl;

    // ---- End Extracting Info from xml ----

    // ---- Generating Menu texts ----
    // Title
    if (language == "en") {
        titleTextShadow = createText(titleStr, midWindowWidth * 90 / 100 + 4, windowHeight * 10 / 100 + 4, 8, Color::Black, "Jedi", "middle");
        titleText = createText(titleStr, midWindowWidth * 90 / 100, windowHeight * 10 / 100, 8, Color::White, "Jedi", "middle");
    } else {
        titleTextShadow = createText(titleStr, midWindowWidth * 90 / 100 + 4, windowHeight * 10 / 100 + 4, 8, Color::Black, "Blanka", "middle");
        titleText = createText(titleStr, midWindowWidth * 90 / 100, windowHeight * 10 / 100, 8, Color::White, "Blanka", "middle");
    }

    // Coders
    codersTextShadow = createText(codersStr, midWindowWidth * 90 / 100 + 2, windowHeight * 23 / 100 + 2, 2, Color::Black, "Anteb", "middle");
    codersText = createText(codersStr, midWindowWidth * 90 / 100, windowHeight * 23 / 100, 2, Color::White, "Anteb", "middle");

    // Language
    std::string languageToUpper = language;  // Não to mudando a language porquê ela vai ser usada pra mudar a linguagem em lowerCase
    for (int i = 0; i < language.size(); i++) {
        languageToUpper[i] = toupper(language[i]);
    }
    languageText = createText(languageToUpper, windowWidth * 95 / 100, windowHeight * 3 / 100, 2, Color::White, "Montserrat", "Right");

    // Language Title Text
    languageTitleText = createText(languageStr, midWindowWidth, midWindowWidth * 23 / 100, 4, Color::Black, "Blanka", "middle");

    // ---- End Menu Texts Generation ----

    // ---- Bandeira em uso ----
    // Colocando a bandeira aqui pra ela atualizar assim que a linguagem mudar

    countryFlagSprite.setTexture(flagsTexture);
    countryFlagSprite.setTextureRect(IntRect(id * flagsTextOffset, 0, flagsTextOffset, flagsTextOffset));
    countryFlagSprite.setScale((float)windowWidth * 0.8 / 1920, (float)windowHeight * 0.8 / 1080);
    countryFlagSprite.setOrigin(countryFlagSprite.getLocalBounds().width, 0);
    countryFlagSprite.setPosition(getInitialPos(languageText).x, getInitialPos(languageText).y - 4);

    // ---- Fim bandeira em uso ----

    // ---- Language Backgrounds ----
    tinyxml2::XMLElement *pLanguage = pLanguages->FirstChildElement();

    // Limpando memoria pra evitar leaks
    for (int i = 0; i < languagesNames.size(); i++) {
        delete languageBackgrounds[i];
        delete languagesNames[i];
    }

    languageBackgrounds.clear();  // Limpando o vector quando muda a lingua
    languagesNames.clear();       // Limpando linguagens pra não duplicar elas

    // Diminuido o tamanho dos vetores pra evitar probmelas com .push_back()
    languageBackgrounds.shrink_to_fit();
    languagesNames.shrink_to_fit();

    // ---- Inicio Settings Menu ----
    settingsString = selectedLang->FirstChildElement("settings")->GetText();
    bombsString = selectedLang->FirstChildElement("bombs")->GetText();

    float leftBoarder = getInitialPos(languageCardSprite).x + 4 * fs;
    float topBoarder = midWindowWidth * 23 / 100 + 7 * fs;

    // Configurações
    settingsTitle = createText(settingsString, midWindowWidth + 2 * fs, midWindowWidth * 23 / 100, 4, Color::Black, "Blanka", "middle");
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
    playerText = createText(selectedLang->FirstChildElement("player")->GetText(), getInitialPos(gameScreenReference).x + 7 * fs + gameScreenReference.getLocalBounds().width * gameScreenReference.getScale().x / 2 - 2 * fs + 2 * fs,
                            getInitialPos(gameScreenReference).y + 2 * fs, 4, Color::Black);

    // ---- Fim Settings Menu ----

    int control = 0;  // Todas as linguas
    while (pLanguage) {
        // Colocando retangulos das linguagens a serem desenhadas dentro de um vector
        RectangleShape *shape = new RectangleShape;
        shape->setSize(Vector2f(languageCardSprite.getLocalBounds().width - 8 * fs, 4 * fs));
        shape->setScale((float)windowWidth / 1920, 1);
        shape->setOrigin(shape->getLocalBounds().width / 2, 0);
        shape->setPosition(midWindowWidth, (float)windowHeight * 320 / 1080 + 5 * fs * control);

        // Mudando a opacidade da linguagem em uso
        if (nameStr == pLanguage->FirstChildElement("name")->GetText()) {
            shape->setFillColor(Color(255, 255, 255, 200));
        } else {
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