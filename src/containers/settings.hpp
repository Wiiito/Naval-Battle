#include "sceneTemp.hpp"

using namespace sf;
using namespace std;

class Settings : public SceneTemp
{
private:
    string bombsCount;
    Text bombsNumberText;

    Text boardWidthNumberText;
    Text boardHeightNumberText;

    int sizeBoardX;
    int sizeBoardY;

    Text twoBoatsText;
    Text threeBoatsText;
    Text fourBoatsText;
    Text fiveBoatsText;

public:
    Settings()
    {
        sizeBoardX = squaresCount.x;
        sizeBoardY = squaresCount.y;
    };

    void drawValuesChanger(Vector2i mousePos, int *variable, Text text, RenderWindow *pWindow)
    {
        Vector2i textStart = {(int)text.getGlobalBounds().left, (int)text.getGlobalBounds().top};
        Vector2i textEnd = {(int)text.getGlobalBounds().left + (int)text.getGlobalBounds().width, (int)text.getGlobalBounds().top + (int)text.getGlobalBounds().height};

        Sprite upper;
        Sprite lower;

        upper.setTexture(mainTexture);
        upper.setTextureRect(IntRect(2 * textureOffset, 2 * textureOffset, textureOffset, textureOffset));

        lower.setTexture(mainTexture);
        lower.setTextureRect(IntRect(3 * textureOffset, 2 * textureOffset, textureOffset, textureOffset));

        upper.setScale((float)windowWidth * 0.5 / 1920, (float)windowHeight * 0.5 / 1080);
        upper.setOrigin(Vector2f(0, 0));
        upper.setPosition(textEnd.x + fs, textStart.y + fs);
        pWindow->draw(upper);

        lower.setScale((float)windowWidth * 0.5 / 1920, (float)windowHeight * 0.5 / 1080);
        lower.setOrigin(Vector2f(0, 0));
        lower.setPosition(textEnd.x + fs, textEnd.y + 0.5 * fs);
        pWindow->draw(lower);

        if (isClickBetween(mousePos, upper))
        {
            (*variable)++;
        }
        if (isClickBetween(mousePos, lower) && (*variable) > 0)
        {
            (*variable)--;
        }
    }

    void update(Engine *pEngine)
    {
        mousePos = {0, 0};

        if (Mouse::isButtonPressed(Mouse::Left) ){
            mousePos = Mouse::getPosition(*pEngine->getWindow());
        }

        if (isClickBetween(mousePos, languageBackButtonSprite)) {
            pEngine->setCurrentScene("menu");
        }

        // /- Bombas -/
        bombsCount = to_string(bombsNumber);
        bombsNumberText = createText(bombsCount, (languageCardSprite.getGlobalBounds().left + languageCardSprite.getGlobalBounds().width) - 9 * fs, bombsTextSettings.getPosition().y, 3, Color::Black, "Anteb", "right");

        // /- Tabuleiro -/
        string boardWidth = to_string(squaresCount.x);
        boardWidthNumberText = createText(boardWidth, (languageCardSprite.getGlobalBounds().left + languageCardSprite.getGlobalBounds().width) - 9 * fs, boardWidthText.getPosition().y, 3, Color::Black, "Anteb", "right");

        string boardHeight = to_string(squaresCount.y);
        boardHeightNumberText = createText(boardHeight, (languageCardSprite.getGlobalBounds().left + languageCardSprite.getGlobalBounds().width) - 9 * fs, boardHeightText.getPosition().y, 3, Color::Black, "Anteb", "right");

        // /- Barcos -/
        string twoBoats = to_string(boatsQuantity[0]);
        string threeBoats = to_string(boatsQuantity[1]);
        string fourBoats = to_string(boatsQuantity[2]);
        string fiveBoats = to_string(boatsQuantity[3]);

        twoBoatsText = createText(twoBoats, (languageCardSprite.getGlobalBounds().left + languageCardSprite.getGlobalBounds().width) - 10 * fs, twoBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");
        threeBoatsText = createText(threeBoats, (languageCardSprite.getGlobalBounds().left + languageCardSprite.getGlobalBounds().width) - 10 * fs, threeBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");
        fourBoatsText = createText(fourBoats, (languageCardSprite.getGlobalBounds().left + languageCardSprite.getGlobalBounds().width) - 10 * fs, fourBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");
        fiveBoatsText = createText(fiveBoats, (languageCardSprite.getGlobalBounds().left + languageCardSprite.getGlobalBounds().width) - 10 * fs, fiveBoatsTextTitle.getPosition().y, 3, Color::Black, "Anteb", "right");
    };
    void render(sf::RenderWindow *pWindow)
    {
        pWindow->draw(menuBgSprite);
        pWindow->draw(languageCardSprite);
        pWindow->draw(languageBackButtonSprite);
        // ---- Settings texts ----

        // Bombs
        pWindow->draw(settingsTitle);
        pWindow->draw(bombsTextSettings);

        pWindow->draw(bombsNumberText);
        drawValuesChanger(mousePos, &bombsNumber, bombsNumberText, pWindow);

        // Tabuleiro
        pWindow->draw(boardText);
        pWindow->draw(boardWidthText);
        pWindow->draw(boardHeightText);

        pWindow->draw(boardWidthNumberText);
        drawValuesChanger(mousePos, &sizeBoardX, boardWidthNumberText, pWindow);
        pWindow->draw(boardHeightNumberText);
        drawValuesChanger(mousePos, &sizeBoardY, boardHeightNumberText, pWindow);
        squaresCount = {sizeBoardX, sizeBoardY};

        pWindow->draw(twoBoatsTextTitle);
        pWindow->draw(threeBoatsTextTitle);
        pWindow->draw(fourBoatsTextTitle);
        pWindow->draw(fiveBoatsTextTitle);

        pWindow->draw(twoBoatsText);
        pWindow->draw(threeBoatsText);
        pWindow->draw(fourBoatsText);
        pWindow->draw(fiveBoatsText);

        drawValuesChanger(mousePos, &boatsQuantity[0], twoBoatsText, pWindow);
        drawValuesChanger(mousePos, &boatsQuantity[1], threeBoatsText, pWindow);
        drawValuesChanger(mousePos, &boatsQuantity[2], fourBoatsText, pWindow);
        drawValuesChanger(mousePos, &boatsQuantity[3], fiveBoatsText, pWindow);

        // Boats
        pWindow->draw(boatsText);
    };
};