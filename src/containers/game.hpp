#pragma once
#include "sceneTemp.hpp"

class Game : public SceneTemp
{
public:
    Game(){};
    Game(Vector2u windowSize){};

    void update(Engine *pEngine, string *pGameMode){};
    void render(sf::RenderWindow *pWindow){};
};