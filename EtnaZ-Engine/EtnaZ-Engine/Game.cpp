#include "Game.h"

#include "GameEngine.h"

Game* Game::instance = nullptr;

Game::Game() {
    right = false;
    left = false;
    mid = false;

    setLayer(4); // layer 3 pour les jauges

    // Position dans la zone entourée : au-dessus de la carte
    float jaugeW = 340.f;
    float jaugeH = 25.f;
    float jaugeX = 1920 / 2 - 250; // bord gauche de la carte
    float jaugeStartY = 1080 / 2 - 350 + 20.f; // haut du cardBackground + marge

    Jauge* softJauge = new Jauge({ jaugeX + 80, jaugeStartY }, { jaugeW, jaugeH }, sf::Color(100, 200, 100), "Soft", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial));
    Jauge* noirJauge = new Jauge({ jaugeX + 80, jaugeStartY + 35 }, { jaugeW, jaugeH }, sf::Color(80, 80, 80), "Noir", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial));
    Jauge* beaufJauge = new Jauge({ jaugeX + 80, jaugeStartY + 70 }, { jaugeW, jaugeH }, sf::Color(200, 150, 50), "Beauf", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial));

    jauges.push_back(softJauge);
    jauges.push_back(noirJauge);
    jauges.push_back(beaufJauge);

    addObjetcInLayer(softJauge, 3);
    addObjetcInLayer(noirJauge, 3);
    addObjetcInLayer(beaufJauge, 3);

    GameObject* block1 = new GameObject({0,0},{ 1920 / 2 - 250, 1080});
    //block1->setColor(sf::Color::Blue);
    checkHover.push_back(block1);
    addObjetcInLayer(block1,1);

    GameObject* throwBtn = new GameObject({ (1920 / 2 - 250) / 2 - 100, 1080 / 2 - 50 }, { 200, 100 });
    throwBtn->setColor(sf::Color::Black);
    throwBtn->setHoverColor(sf::Color::Red);
    throwBtn->setText("Throw",
        Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial),
        48);
    entity.push_back(throwBtn);
    addObjetcInLayer(throwBtn, 2); // layer au-dessus de block1

    GameObject* block2 = new GameObject({ 1920 / 2 + 250, 0}, { 1920 / 2 - 250, 1080 });
    //block2->setColor(sf::Color::Blue); 
    checkHover.push_back(block2);
    addObjetcInLayer(block2, 1);

    // Bouton Take par-dessus block2
    float block2X = 1920.f / 2.f + 250.f;
    float block2W = 1920.f / 2.f - 250.f;
    GameObject* takeBtn = new GameObject({ block2X + block2W / 2 - 100, 1080 / 2 - 50 }, { 200, 100 });
    takeBtn->setColor(sf::Color::Black);
    takeBtn->setHoverColor(sf::Color::Green);
    takeBtn->setText("Take",
        Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial),
        48);
    entity.push_back(takeBtn);
    addObjetcInLayer(takeBtn, 2);

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
    hoverEffect();
    if (entity[0]->isClicked()) {
        entity.pop_back();
        nextCard();
    }
    else if (entity[1]->isClicked()) {
        entity.pop_back();
        nextCard();
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

void Game::hoverEffect() {
    if (checkHover[0]->isHover()) {
        mid = false;
        left = false;
        right = true;
    }
    else if (checkHover[1]->isHover()) {
        mid = false;
        left = true;
        right = false;
    }
    else {
        mid = true;
        left = false;
        right = false;
    }
    
    entity.back()->rotate(right, left);
}

void Game::nextCard() {

}
