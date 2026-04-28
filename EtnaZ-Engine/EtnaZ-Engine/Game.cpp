#include "Game.h"

#include "GameEngine.h"

Game* Game::instance = nullptr;

Game::Game() {
    setLayer(3);

    GameObject* block1 = new GameObject({0,0},{ 1920 / 2 - 250, 1080 / 2 - 350 });
    block1->setColor(sf::Color::Blue);
    checkHover.push_back(block1);
    addObjetcInLayer(block1,1);

    GameObject* block2 = new GameObject({ 1920 / 2 - 210, 1080 / 2 - 230 }, { 1920 / 2 - 250, 1080 / 2 - 350 });
    block2->setColor(sf::Color::Blue); 
    checkHover.push_back(block2);
    addObjetcInLayer(block2, 1);

    GameObject* background = new GameObject({0,0},{1920,1080});
    background->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::background));
    addObjetcInLayer(background, 0);

    GameObject* cardBackground = new GameObject({ 1920 / 2-250, 1080 / 2-350 }, { 500, 700 });
    cardBackground->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card_background));
    addObjetcInLayer(cardBackground, 1);

    GameObject* card = new GameObject({ 1920 / 2 - 210, 1080 / 2 - 230 }, { 420, 550 });
    card->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card));
    entity.push_back(card);
    addObjetcInLayer(card,2);
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
    for (auto& cH : checkHover) {
        if (cH->isHover()) {
            entity.back()->rotateRight();
        }
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
