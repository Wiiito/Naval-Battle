#include "header.hpp"

void settings() {
    Vector2i mousePos;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (Mouse::isButtonPressed(Mouse::Left))
            mousePos = Mouse::getPosition(window);
    }

    if (isClickBetween(mousePos, languageBackButtonSprite)) {
        controlPanel = 4;
    }

    // Os valores mudam, então a criação do texto deve ficar dentro da função atualizada todo frame

    // /- Bombas -/
    std::string bombsCount = std::to_string(bombsNumber);
    Text bombsNumberText = createText(bombsCount, getFinalPos(languageCardSprite).x - 9 * fs, bombsTextSettings.getPosition().y, 3, Color::Black, "Anteb", "right");

    // /- Tabuleiro -/
    std::string boardWidth = std::to_string(sizeBoardX);
    Text boardWidthNumberText = createText(boardWidth, getFinalPos(languageCardSprite).x - 9 * fs, boardWidthText.getPosition().y, 3, Color::Black, "Anteb", "right");

    std::string boardHeight = std::to_string(sizeBoardY);
    Text boardHeightNumberText = createText(boardHeight, getFinalPos(languageCardSprite).x - 9 * fs, boardHeightText.getPosition().y, 3, Color::Black, "Anteb", "right");

    // /- Barcos -/
    std::string twoBoats = std::to_string(boatsQuantity[0]);
    std::string threeBoats = std::to_string(boatsQuantity[1]);
    std::string fourBoats = std::to_string(boatsQuantity[2]);
    std::string fiveBoats = std::to_string(boatsQuantity[3]);

    Text twoBoatsText = createText(twoBoats, getFinalPos(languageCardSprite).x - 10 * fs, twoBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");
    Text threeBoatsText = createText(threeBoats, getFinalPos(languageCardSprite).x - 10 * fs, threeBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");
    Text fourBoatsText = createText(fourBoats, getFinalPos(languageCardSprite).x - 10 * fs, fourBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");
    Text fiveBoatsText = createText(fiveBoats, getFinalPos(languageCardSprite).x - 10 * fs, fiveBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");

    window.clear(Color::White);
    window.draw(menuBgSprite);
    window.draw(languageCardSprite);
    window.draw(languageBackButtonSprite);
    // ---- Settings texts ----

    // Bombs
    window.draw(settingsTitle);
    window.draw(bombsTextSettings);

    window.draw(bombsNumberText);
    drawValuesChanger(mousePos, &bombsNumber, bombsNumberText);

    // Tabuleiro
    window.draw(boardText);
    window.draw(boardWidthText);
    window.draw(boardHeightText);

    window.draw(boardWidthNumberText);
    drawValuesChanger(mousePos, &sizeBoardX, boardWidthNumberText);
    window.draw(boardHeightNumberText);
    drawValuesChanger(mousePos, &sizeBoardY, boardHeightNumberText);

    window.draw(twoBoatsTextTitle);
    window.draw(threeBoatsTextTitle);
    window.draw(fourBoatsTextTitle);
    window.draw(fiveBoatsTextTitle);

    window.draw(twoBoatsText);
    window.draw(threeBoatsText);
    window.draw(fourBoatsText);
    window.draw(fiveBoatsText);

    drawValuesChanger(mousePos, &boatsQuantity[0], twoBoatsText);
    drawValuesChanger(mousePos, &boatsQuantity[1], threeBoatsText);
    drawValuesChanger(mousePos, &boatsQuantity[2], fourBoatsText);
    drawValuesChanger(mousePos, &boatsQuantity[3], fiveBoatsText);

    // Boats
    window.draw(boatsText);

    window.display();
}