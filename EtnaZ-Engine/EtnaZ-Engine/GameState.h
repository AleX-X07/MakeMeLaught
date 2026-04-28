#pragma once

// Forward declaration
// #####
class GameEngine;
// #####


// Class for make a scene
// #####
class GameState {
protected:
    // Constructor
    GameState() = default;

public:
    // Destructor
    virtual ~GameState() = default;

    // Method for act on scene
    void nextState();
    void pause();
    void resume();

    // Method for heritage
    virtual void manageState() = 0;
    virtual void update(float& dt) = 0;
    virtual void render() = 0;
};
// #####