#include <SFML/Graphics.hpp>
#include <iostream>

#include "src/containers/menu.hpp"
#include "src/containers/chooseMode.hpp"
#include "src/containers/game.hpp"

// #include "src/header.hpp"

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
  string *gameMode = new string("MP");

  // ---- Creating menuScene ----
  Menu *menu = new Menu;
  Scene menuScene("menu");
  menuScene.setInstanceFunction([&menu, pWindow]() -> void
                                {
    delete (menu);
    menu = new Menu(pWindow->getSize()); });
  menuScene.add([menu, pWindow, &gameEngine]() -> void
                {
    menu->update(&gameEngine);
    menu->render(pWindow); });
  gameEngine.pushScene(&menuScene);

  // ---- Creating chooseMScene ----
  chooseMode *chooseM = new chooseMode;
  Scene chooseMScene("chooseMode");
  chooseMScene.setInstanceFunction([&chooseM, pWindow]() -> void
                                   {
    delete (chooseM);
    chooseM = new chooseMode(pWindow->getSize()); });
  chooseMScene.add([chooseM, pWindow, &gameEngine, gameMode]() -> void
                   {
    chooseM->update(&gameEngine, gameMode);
    cout << "Fora: " << *gameMode << endl;
    chooseM->render(pWindow); });
  gameEngine.pushScene(&chooseMScene);


  // ---- Creating gameScene ----
  Game *game = new Game;
  Scene gameScene("game");
  gameScene.setInstanceFunction([&game, pWindow]() -> void
                                {
    delete (game);
    game = new Game(pWindow->getSize()); });
  gameScene.add([game, pWindow, &gameEngine, gameMode]() -> void
                {
    game->update(&gameEngine, gameMode);
    game->render(pWindow); });
  gameEngine.pushScene(&gameScene);

  // Set the initial scene
  gameEngine.setCurrentScene("menu");

  // Runs the game
  while (gameEngine.getIsWindowOpen())
  {
    gameEngine.updateGame();
  }
}
