#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "GameState.h"
#include "Menu.h"
#include "Textures.h"

class GameEngine;

class Game : public GameState {

private:
    // Variable for scene
    Game();

    static Game* instance;

    std::vector<GameObject*> entity;
    std::vector<GameObject*> checkHover;

    std::vector<std::vector<GameObject*>> vecRender;

    bool right;
    bool left;
    bool mid;

private:

public:
    virtual ~Game() override;

    static GameState* getInstance();

    virtual void manageState() override;
    virtual void update(float& dt) override;
    virtual void render() override;

    void hoverEffect();

    // Layer
    void addObjetcInLayer(GameObject* myObject, int Layer);
    void setLayer(int nbrLayer);
};