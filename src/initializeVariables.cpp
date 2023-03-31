#include "header.hpp"

// Variables that need yo be initialized only one time will be here

void initializeVar() {
    // Fonte initialization
    fontAnteb.loadFromFile("src/assets/fonts/Anteb-Regular.ttf");
    fontBlanka.loadFromFile("src/assets/fonts/Blanka-Regular.otf");
    fontJedi.loadFromFile("src/assets/fonts/STARJEDI.TTF");

    //  Menu Background
    menuBgTx.loadFromFile("src/assets/menuBackground.png");
    menuBgSprite.setTexture(menuBgTx);
    menuBgSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    menuBgSprite.setOrigin(menuBgSprite.getLocalBounds().width / 2, menuBgSprite.getLocalBounds().height / 2);
    menuBgSprite.setPosition(midWindowWidth, midWindowHeight);

    //  Menu Start Button
    btnTx.loadFromFile("src/assets/startButton.png");
    btnSprite.setTexture(btnTx);
    btnSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    btnSprite.setOrigin(btnSprite.getLocalBounds().width / 2, btnSprite.getLocalBounds().height / 2);
    btnSprite.setPosition(midWindowWidth * 90 / 100, windowHeight * 78 / 100);

    //  Menu Settings Button
    settingsTx.loadFromFile("src/assets/settings.png");
    settingsSprite.setTexture(settingsTx);
    settingsSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    settingsSprite.setOrigin(0, settingsSprite.getLocalBounds().height);
    settingsSprite.setPosition(windowWidth * 2 / 100, windowHeight * 96 / 100);

    //  Menu Settings Button
    quitTx.loadFromFile("src/assets/quit.png");
    quitSprite.setTexture(quitTx);
    quitSprite.setScale((float)windowWidth / 1920, (float)windowHeight / 1080);
    quitSprite.setOrigin(quitSprite.getLocalBounds().width, quitSprite.getLocalBounds().height);
    quitSprite.setPosition(windowWidth * 98 / 100, windowHeight * 96 / 100);

    updateText();  // First generation of the text
}

void updateText() {
    tinyxml2::XMLDocument doc;  // Declarando aqui dentro pra quando sair da função, fechar
    doc.LoadFile("src/lang/languages.xml");

    tinyxml2::XMLElement *pRootElement = doc.RootElement();
    tinyxml2::XMLElement *pLastLang = pRootElement->FirstChildElement("lastLang");  // Pegando a ultima lingua utilizada pelo usuario

    std::string codersStr = pRootElement->FirstChildElement("coders")->GetText();

    tinyxml2::XMLElement *pLanguages = pRootElement->FirstChildElement("languages");
    tinyxml2::XMLElement *selectedLang = pLanguages->FirstChildElement(pLastLang->GetText());

    // Saving pointers to string
    std::string titleStr = selectedLang->FirstChildElement("title")->GetText();

    // Generating texts
    // Coders
    codersTextShadow = createText(codersStr, midWindowWidth * 90 / 100 + 2, windowHeight * 23 / 100 + 2, 2, Color::Black, "Anteb", "middle");
    codersText = createText(codersStr, midWindowWidth * 90 / 100, windowHeight * 23 / 100, 2, Color::White, "Anteb", "middle");

    // Title
    std::string language = pLastLang->GetText();
    if (language == "en") {
        titleTextShadow = createText(titleStr, midWindowWidth * 90 / 100 + 4, windowHeight * 10 / 100 + 4, 8, Color::Black, "Jedi", "middle");
        titleText = createText(titleStr, midWindowWidth * 90 / 100, windowHeight * 10 / 100, 8, Color::White, "Jedi", "middle");
    } else {
        titleTextShadow = createText(titleStr, midWindowWidth * 90 / 100 + 4, windowHeight * 10 / 100 + 4, 8, Color::Black, "Blanka", "middle");
        titleText = createText(titleStr, midWindowWidth * 90 / 100, windowHeight * 10 / 100, 8, Color::White, "Blanka", "middle");
    }
}