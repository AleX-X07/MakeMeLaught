#include "Game.h"

#include "GameEngine.h"

Game* Game::instance = nullptr;

Game::Game() {
    GameObject* card = new GameObject({ 1920 / 2-150, 1080 / 2-250 }, { 300, 500 });
    entity.push_back(card);

    setLayer(3);
    addObjetcInLayer(card, 0);
}

Game::~Game() {
    instance = nullptr;
}

GameState* Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::manageState() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        nextState();
        GameEngine::states.push_back(Menu::getInstance());
    }
}

void Game::update(float& dt) {
    for (auto& e : entity) {
        e->update(dt);
   }
}

void Game::render() {
    for (auto& vR : vecRender) {
        for (auto& v : vR) {
            v->render();
        }
    }
}

void Game::addObjetcInLayer(GameObject* myObject, int Layer) {
    if (!vecRender.empty() && Layer < vecRender.size()) {
        vecRender[Layer].push_back(myObject);
    }
}

void Game::setLayer(int _nbrLayer) {
    for (int X = 0; X < _nbrLayer; X++) {
        std::vector<GameObject*>  layer;
        vecRender.push_back(layer);
    }
}
