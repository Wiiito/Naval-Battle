#include "sceneTemp.hpp"

using namespace sf;
using namespace std;

class FinalScreen : public SceneTemp
{
private:
    Text playerCongratsText;
public:
    FinalScreen(){};

    void update(Engine *pEngine)
    {
        mousePos = {0, 0};
        if (Mouse::isButtonPressed(Mouse::Left))
            mousePos = Mouse::getPosition(*pEngine->getWindow());

        if (win) {
            if (gameMode == "SP")
                playerCongratsText = createText(congratulationsText.getString() + ", " + wonString + "!", windowWidth / 2, gameScreenReference.getGlobalBounds().top + 15 * fs, 5, Color::Black, "Anteb", "middle");
            else if (gameMode == "MP")
                playerCongratsText = createText(congratulationsText.getString() + " " + playerText.getString() + " " + std::to_string(!currentPlayer + 1) + ", " + wonString + "!", windowWidth / 2, gameScreenReference.getGlobalBounds().top + 15 * fs, 5, Color::Black, "Anteb", "middle");
        } else {
            congratulationsText = createText(loseString, windowWidth / 2,
                          gameScreenReference.getGlobalBounds().top + 5 * fs, 8, Color::Black, "Blanka", "middle");
        
            playerCongratsText = createText("", 0, 0, 0, Color::Transparent);
        }

        if (isClickBetween(mousePos, endScreenBackButton))
        {
            pEngine->getWindow()->close();
        }
        if (isClickBetween(mousePos, endScreenPlayAgain))
        {
            pEngine->setCurrentScene("menu");
        }
    };

    void render(sf::RenderWindow *pWindow)
    {
        pWindow->draw(gameBackgroundSprite);
        pWindow->draw(congratulationsText);
        pWindow->draw(playerCongratsText);
        pWindow->draw(endScreenBackButton);
        pWindow->draw(endScreenPlayAgain);
    };
};