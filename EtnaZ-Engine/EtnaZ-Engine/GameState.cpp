#include "GameState.h"
#include "GameEngine.h"

// Function which pop the current scene f or put the other after
// ######
void GameState::nextState() {
    if (!GameEngine::states.empty()) {
        GameEngine::states.pop_back();
    }
}
// ######

// Function for pause a scene
// ######
void GameState::pause() {
    
}
// ######

// Function for resume a scene
// ######
void GameState::resume() {
    
}
// ######
