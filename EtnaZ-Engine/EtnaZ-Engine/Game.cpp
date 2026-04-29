#include "Game.h"
#include "GameEngine.h"

Game* Game::instance = nullptr;

Game::Game() {
    right = false;
    left = false;
    mid = false;

    setLayer(5);

    float jaugeW = 340.f;
    float jaugeH = 25.f;
    float jaugeX = 1920 / 2 - 250;
    float jaugeStartY = 1080 / 2 - 350 + 20.f;

    softJauge = new Jauge({ jaugeX + 80, jaugeStartY }, { jaugeW, jaugeH }, sf::Color::Red, "Soft", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial));
    noirJauge = new Jauge({ jaugeX + 80, jaugeStartY + 35 }, { jaugeW, jaugeH }, sf::Color::Green, "Noir", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial));
    beaufJauge = new Jauge({ jaugeX + 80, jaugeStartY + 70 }, { jaugeW, jaugeH }, sf::Color::Blue, "Beauf", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial));

    jauges.push_back(softJauge);
    jauges.push_back(noirJauge);
    jauges.push_back(beaufJauge);

    addObjetcInLayer(softJauge, 3);
    addObjetcInLayer(noirJauge, 3);
    addObjetcInLayer(beaufJauge, 3);

    // Zones de hover (invisibles)
    GameObject* block1 = new GameObject({ 0, 0 }, { 1920 / 2 - 250, 1080 });
    checkHover.push_back(block1);
    addObjetcInLayer(block1, 1);

    // Bouton Throw
    GameObject* throwBtn = new GameObject({ (1920 / 2 - 250) / 2 - 100, 1080 / 2 - 50 }, { 200, 100 });
    throwBtn->setColor(sf::Color::Black);
    throwBtn->setHoverColor(sf::Color::Red);
    throwBtn->setText("Throw", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial), 48);
    entity.push_back(throwBtn);
    addObjetcInLayer(throwBtn, 2);

    // Zone de hover droite
    GameObject* block2 = new GameObject({ 1920 / 2 + 250, 0 }, { 1920 / 2 - 250, 1080 });
    checkHover.push_back(block2);
    addObjetcInLayer(block2, 1);

    // Bouton Take
    float block2X = 1920.f / 2.f + 250.f;
    float block2W = 1920.f / 2.f - 250.f;
    GameObject* takeBtn = new GameObject({ block2X + block2W / 2 - 100, 1080 / 2 - 50 }, { 200, 100 });
    takeBtn->setColor(sf::Color::Black);
    takeBtn->setHoverColor(sf::Color::Green);
    takeBtn->setText("Take", Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial), 48);
    entity.push_back(takeBtn);
    addObjetcInLayer(takeBtn, 2);

    // Background
    GameObject* background = new GameObject({ 0, 0 }, { 1920, 1080 });
    background->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::background));
    addObjetcInLayer(background, 0);

    // Card background
    GameObject* cardBackground = new GameObject({ 1920 / 2 - 250, 1080 / 2 - 350 }, { 500, 700 });
    cardBackground->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card_background));
    addObjetcInLayer(cardBackground, 1);

    // Cartes — taille 420x550, zone blanche dans le bas → offset Y +130
    sf::Font& font = Textures::getTexturesManager()->getFont(Textures::fontsIndices::arial);
    sf::Vector2f cardPos = { 1920.f / 2.f - 210.f, 1080.f / 2.f - 230.f };
    sf::Vector2f cardSize = { 420.f, 550.f };
    sf::Vector2f textOffset = { -750, -550 };

    //GameObject* card = new GameObject(cardPos, cardSize);
    //card->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card));
    //card->setCardType(GameObject::cardType::soft);
    //card->setText("Quelle mamie fait peur aux voleurs ? \n Mamie Traillette.", font, 25, sf::Color::Black, textOffset);
    //cardVec.push_back(card);

    //GameObject* card2 = new GameObject(cardPos, cardSize);
    //card2->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card2));
    //card2->setCardType(GameObject::cardType::noir);
    //card2->setText("Texte card 2", font, 25, sf::Color::Black, textOffset);
    //cardVec.push_back(card2);

    //GameObject* card3 = new GameObject(cardPos, cardSize);
    //card3->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card3));
    //card3->setCardType(GameObject::cardType::beauf);
    //card3->setText("Texte card 3", font, 25, sf::Color::Black, textOffset);
    //cardVec.push_back(card3);

    //// On démarre sur la première carte (qui a le texte)
    //currentCard = cardVec[0];
    //addObjetcInLayer(currentCard, 4);

    auto cards = CardLoader::loadFromFile("Assets/Blagues.txt");
    for (auto& data : cards) {
        GameObject* card = new GameObject(cardPos, cardSize);

        // Choisit la texture selon le type
        switch (data.type) {
        case GameObject::cardType::soft:  card->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card));   break;
        case GameObject::cardType::noir:  card->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card2));  break;
        case GameObject::cardType::beauf: card->setTextures(Textures::getTexturesManager()->getTexture(Textures::texturesIndices::card3));  break;
        }

        card->setCardType(data.type);
        card->setText(data.text, font, 25, sf::Color::Black, textOffset);
        cardVec.push_back(card);
    }

    currentCard = cardVec[0];
    addObjetcInLayer(currentCard, 4);
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
        nextCard();
    }
    else if (entity[1]->isClicked()) {
        switch (currentCard->getCardType()) {
        case GameObject::cardType::soft:  softJauge->increase(currentCard->getVal() / 100.f);  break;
        case GameObject::cardType::noir:  noirJauge->increase(currentCard->getVal() / 100.f);  break;
        case GameObject::cardType::beauf: beaufJauge->increase(currentCard->getVal() / 100.f); break;
        }
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
    if (!vecRender.empty() && Layer < (int)vecRender.size()) {
        vecRender[Layer].push_back(myObject);
    }
}

void Game::supprObjectInLayer(int id, int layer) {
    vecRender[layer].erase(vecRender[layer].begin() + id);
}

void Game::setLayer(int _nbrLayer) {
    for (int X = 0; X < _nbrLayer; X++) {
        std::vector<GameObject*> layer;
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

    currentCard->rotate(right, left);
}

void Game::nextCard() {
    int a = GameObject::getRandomNumber(0, cardVec.size() - 1);
    currentCard = cardVec[a];
    supprObjectInLayer(0, 4);
    addObjetcInLayer(cardVec[a], 4);
}