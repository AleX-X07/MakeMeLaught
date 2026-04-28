#pragma once
#include "SFML/Graphics.hpp"
#include "Input.h"
#include "GameState.h"
#include "Game.h"

class GameEngine {
public:
    // Static variable
    static sf::RenderWindow* window;
    // Vector for states in pause
    static std::vector<GameState*> states;

private:
    // Variable
    sf::Clock clock;
    float dt;

public:

    // Constructor/Destructor
    GameEngine();
    ~GameEngine();

    // Update
    void updateEvent();
    void updateTime();
    void update();

    //render
    void render();

    // main loop
    void run();
};