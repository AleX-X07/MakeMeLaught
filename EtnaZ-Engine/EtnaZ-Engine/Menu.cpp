#include "Menu.h"
#include "GameEngine.h"
#include "Game.h"

Menu* Menu::instance = nullptr;

Menu::Menu() {

}

Menu::~Menu() {

}

GameState* Menu::getInstance() {
    if (instance == nullptr) {
        instance = new Menu();
    }
    return instance;
}

void Menu::manageState() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        nextState();
        GameEngine::states.push_back(Game::getInstance());
    }
}

void Menu::update(float& dt) {

}

void Menu::render() {
    std::cout << "Menu" << std::endl;
}
