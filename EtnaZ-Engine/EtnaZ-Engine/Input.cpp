#include "Input.h"

#include "SFML/Window/Event.hpp"

// Initialise the instance
// #####
Input* Input::instance = nullptr;
// #####


// Constructor 
// #####
Input::Input() : keyPressed(false), mousePressed(false), mousePos({ 0,0 }) {
    key = {};
    mouse = {};
    mousePos = {};
}
// #####


// Take event, to bind the key which is pressed
// #####
void Input::setEvent(sf::Event event) {
    if (auto* k = event.getIf<sf::Event::KeyPressed>()) {
        keyPressed = true;
        key = k->code;
    }
    else if (auto* m = event.getIf<sf::Event::MouseButtonPressed>()) {
        mousePressed = true;
        mouse = m->button;
        mousePos = m->position;
    }
}
// #####

// Rest the key which are save
// #####
void Input::reset() {
    keyPressed = false;
    mousePressed = false;
}
// #####

// Check if key is pressed (or mouse)
// #####
bool Input::isKeyPressed(sf::Keyboard::Key _key) {
    return keyPressed && key == _key;
}

bool Input::isMousePressed(sf::Mouse::Button _button) {
    return mousePressed && mouse == _button;
}
// #####

// Get mouse pos
// #####
sf::Vector2i Input::getMousePos() {
    return mousePos;
}
// #####


// Get class input (singleton)
// #####
Input* Input::getInstance() {
    if (instance == nullptr) {
        instance = new Input();
    }
    return instance;
}
// #####