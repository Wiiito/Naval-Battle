#include <SFML/Graphics.hpp>
#include <iostream>

#include "src/headers/engine.hpp"
#include "src/containers/menu.hpp"

//#include "src/header.hpp"

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

int main() {
  std::srand(std::time(nullptr));

  // Initial sound configuration

  Engine gameEngine;

  sf::RenderWindow *pWindow = gameEngine.getWindow();

  // ---- Creating menuScene ----
  Menu *menu = new Menu;
  Scene menuScene("menu");
  menuScene.setInstanceFunction([&menu, pWindow]() -> void {
    delete (menu);
    menu = new Menu(pWindow->getSize());
  });
  menuScene.add([menu, pWindow, &gameEngine]() -> void {
    menu->update(&gameEngine);
    menu->render(pWindow);
  });
  gameEngine.pushScene(&menuScene);

  // Set the initial scene
  gameEngine.setCurrentScene("menu");

  // Runs the game
  while (gameEngine.getIsWindowOpen()) {
    gameEngine.updateGame();
  }
}
