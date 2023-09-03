#include "sceneTemp.hpp"

using namespace sf;
using namespace std;

class LangMenu : public SceneTemp
{
public:
    LangMenu(){};

    void update(Engine *pEngine)
    {
        mousePos = {0, 0};

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            mousePos = Mouse::getPosition(*pEngine->getWindow());
        }

        if (isClickBetween(mousePos, languageBackButtonSprite))
        {
            pEngine->setCurrentScene("menu");
        }
    };

    void render(sf::RenderWindow *pWindow)
    {
        pWindow->clear(Color::White);
        pWindow->draw(menuBgSprite);
        pWindow->draw(languageCardSprite);
        pWindow->draw(languageTitleText);

        for (int i = 0; i < languageBackgrounds.size(); i++)
        {
            std::string currentCountryName = languagesNames.at(i)->getString();

            // Checking click
            if (isClickBetween(mousePos, *languageBackgrounds.at(i)))
            {
                pLastLang->SetText(&currentCountryName[0]);
                doc.SaveFile("src/lang/languages.xml");
                updateText();
            }

            // Desenhando bandeiras
            inDrawSprite.setTexture(flagsTexture);
            inDrawSprite.setTextureRect(IntRect(i * flagsTextOffset, 0, flagsTextOffset, flagsTextOffset));
            inDrawSprite.setPosition(languageBackgrounds[i]->getGlobalBounds().left + 2 * fs, languageBackgrounds[i]->getPosition().y);

            pWindow->draw(*languageBackgrounds[i]);
            pWindow->draw(*languagesNames[i]);
            pWindow->draw(inDrawSprite);
        }

        pWindow->draw(languageBackButtonSprite);
    };
};