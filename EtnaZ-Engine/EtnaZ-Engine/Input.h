#pragma once
#include "SFMl/Graphics.hpp"

// Singleton for Input
// #####
class Input {
private:
    // Variable
    // Keyboard
    bool keyPressed;
    sf::Keyboard::Key key;

    // Mouse
    bool mousePressed;
    sf::Mouse::Button mouse;
    sf::Vector2i mousePos;

    // Constructor private for singleton
    Input();

    // My instance
    static Input* instance;

public:
    // Destructor
    ~Input() = default;

    // Function for the main loop
    void setEvent(sf::Event event);
    void reset();

    // Check input
    bool isKeyPressed(sf::Keyboard::Key key);
    bool isMousePressed(sf::Mouse::Button button);
    sf::Vector2i getMousePos();

    // Get input
    static Input* getInstance();
};
// #####