#include <SFML/Graphics.hpp>
#include <iostream>

#include "src/containers/menu.hpp"
#include "src/containers/chooseMode.hpp"
#include "src/containers/game.hpp"
#include "src/containers/settings.hpp"
#include "src/containers/langMenu.hpp"
#include "src/containers/finalScreen.hpp"

/**
 * Todos os ponteiros para objetos do jogo são chamados aqui pois não podem ser retirados da
 * memoria. As cenas são configuradas aqui para evitar "param hell", em resumo, pra saber o que é o
 * que e de onde vem.
 */

/*class Model {
public:
  Model() { };
  void update(Engine *pEngine) { };
  void render(sf::RenderWindow * pWindow) { };
};*/

int main()
{
  std::srand(std::time(nullptr));

  // Initial sound configuration

  Engine gameEngine;

  sf::RenderWindow *pWindow = gameEngine.getWindow();

  SceneTemp::defTextures(pWindow->getSize());

  // ---- Creating menuScene ----
  Menu *menu = new Menu;
  Scene menuScene("menu");
  menuScene.setInstanceFunction([&menu]() -> void
                                {
    delete (menu);
    menu = new Menu(); });
  menuScene.add([menu, pWindow, &gameEngine]() -> void
                {
    menu->update(&gameEngine);
    menu->render(pWindow); });
  gameEngine.pushScene(&menuScene);

  // ---- Creating chooseMScene ----
  chooseMode *chooseM = new chooseMode;
  Scene chooseMScene("chooseMode");
  chooseMScene.setInstanceFunction([&chooseM]() -> void
                                   {
    delete (chooseM);
    chooseM = new chooseMode(); });
  chooseMScene.add([chooseM, pWindow, &gameEngine]() -> void
                   {
    chooseM->update(&gameEngine);
    chooseM->render(pWindow); });
  gameEngine.pushScene(&chooseMScene);

  // ---- Creating gameScene ----
  Game *game = new Game;
  Scene gameScene("game");
  gameScene.setInstanceFunction([&game]() -> void
                                {
    delete (game);
    game = new Game(); });
  gameScene.add([game, pWindow, &gameEngine]() -> void
                { game->update(&gameEngine); });
  gameEngine.pushScene(&gameScene);

  // ---- Creating settingsScene ----
  Settings *settings = new Settings;
  Scene settingsScene("settings");
  settingsScene.setInstanceFunction([&settings, pWindow]() -> void
                                    {
    delete (settings);
    settings = new Settings(); });
  settingsScene.add([settings, pWindow, &gameEngine]() -> void
                    {
    settings->update(&gameEngine);
    settings->render(pWindow); });
  gameEngine.pushScene(&settingsScene);

  // ---- Creating langMenuScene ----
  LangMenu *langMenu = new LangMenu;
  Scene langMenuScene("langMenu");
  langMenuScene.setInstanceFunction([&langMenu, pWindow]() -> void
                                    {
    delete (langMenu);
    langMenu = new LangMenu(); });
  langMenuScene.add([langMenu, pWindow, &gameEngine]() -> void
                    {
    langMenu->update(&gameEngine);
    langMenu->render(pWindow); });
  gameEngine.pushScene(&langMenuScene);

  // ---- Creating finalScene ----
  FinalScreen *finalScreen = new FinalScreen;
  Scene finalScene("finalScreen");
  finalScene.setInstanceFunction([&finalScreen]() -> void
                                {
    delete (finalScreen);
    finalScreen = new FinalScreen(); });
  finalScene.add([finalScreen, pWindow, &gameEngine]() -> void
                {
    finalScreen->update(&gameEngine);
    finalScreen->render(pWindow); });
  gameEngine.pushScene(&finalScene);

  // Set the initial scene
  gameEngine.setCurrentScene("menu");

  // Runs the game
  while (gameEngine.getIsWindowOpen())
  {
    gameEngine.updateGame();
  }
}
