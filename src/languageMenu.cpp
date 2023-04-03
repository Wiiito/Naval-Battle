#include "header.hpp"

void languagePanel() {
    Vector2i mousePos;  // Limpando o valor todo frame

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (Mouse::isButtonPressed(Mouse::Left)) {
            mousePos = Mouse::getPosition(window);
        }
    }

    window.clear(Color::White);
    window.draw(menuBgSprite);
    window.draw(languageCardSprite);
    window.draw(languageTitleText);

    for (int i = 0; i < languageBackgrounds.size(); i++) {
        std::string currentCountryName = languagesNames[i]->getString();

        // Checking click
        if (isClickBetween(mousePos, *languageBackgrounds[i])) {
            pLastLang->SetText(&currentCountryName[0]);
            doc.SaveFile("src/lang/languages.xml");
            updateText();
        }

        // Desenhando bandeiras
        inUseTexture.loadFromFile("src/assets/flags/" + currentCountryName + ".png");
        inDrawSprite.setTexture(inUseTexture);
        inDrawSprite.setPosition(getInitialPos(*languageBackgrounds[i]).x + 2 * fs, languageBackgrounds[i]->getPosition().y);

        window.draw(*languageBackgrounds[i]);
        window.draw(*languagesNames[i]);
        window.draw(inDrawSprite);
    }

    if (isClickBetween(mousePos, languageBackButtonSprite)) {
        controlPanel = 4;
    }

    window.draw(languageBackButtonSprite);
    window.display();
}