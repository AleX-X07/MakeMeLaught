#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject(sf::Vector2f Pos, sf::Vector2f Size){
	myTextures = nullptr;
    color = nullptr;
	myShape.setPosition(Pos);
	myShape.setSize(Size);

    left = false;
    right = false;
    rotate = false;
}

void GameObject::setTextures(sf::Texture& texture) {
	myTextures = &texture;
}

void GameObject::setColor(sf::Color _color) {
    color = &_color;
}

bool GameObject::isClicked() {
    if (Input::getInstance()->isMousePressed(sf::Mouse::Button::Left)) {
        mousePos = Input::getInstance()->getMousePos();
        if (mousePos.x >= myShape.getPosition().x &&
            mousePos.x <= myShape.getPosition().x + myShape.getSize().x &&
            mousePos.y >= myShape.getPosition().y &&
            mousePos.y <= myShape.getPosition().y + myShape.getSize().y) {
            return true;
        }
    }
    return false;
}

bool GameObject::isHover() {
    mousePos = sf::Mouse::getPosition(*GameEngine::window);
    if (myShape.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
        return true;
    }
    return false;
}

void GameObject::rotateRight() {
    if (!rotate) {
        sf::Angle angle;
        if (right) {
            angle = sf::degrees(45);
        }
        else {
            angle = sf::degrees(-45);
        }
        myShape.rotate(angle);
    }
}

void GameObject::update(float& dt) {

}

void GameObject::render() {
	if (myTextures != nullptr) {
		myShape.setTexture(myTextures);
		GameEngine::window->draw(myShape);
	}
    if (color != nullptr) {
        myShape.setFillColor(*color);
        GameEngine::window->draw(myShape);
    }
}
