#pragma once
#include <iostream>

#include "GameState.h"

class GameEngine;

class Game;

class Menu : public GameState {

private:
    Menu();

    static Menu* instance;

public:
    virtual ~Menu() override;

    static GameState* getInstance();

    virtual void manageState() override;
    virtual void update(float& dt) override;
    virtual void render() override;
};
