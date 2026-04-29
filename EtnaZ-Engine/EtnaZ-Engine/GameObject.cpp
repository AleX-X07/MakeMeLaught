#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject(sf::Vector2f Pos, sf::Vector2f Size){
	myTextures = nullptr;
    hasColor = false;
	myShape.setPosition(Pos);
	myShape.setSize(Size);
}

void GameObject::setTextures(sf::Texture& texture) {
	myTextures = &texture;
}

void GameObject::setColor(sf::Color _color) {
    color = _color;
    hasColor = true;
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

void GameObject::rotate(bool right, bool left) {
    sf::Vector2f size = myShape.getSize();
    sf::Vector2f topLeft = myShape.getPosition() - myShape.getOrigin();

    if (left) {
        myShape.setOrigin({ size.x, size.y });
        myShape.setPosition(topLeft + sf::Vector2f(size.x, size.y));
        myShape.setRotation(sf::degrees(15));
    }
    else if (right) {
        myShape.setOrigin({ 0.f, size.y });
        myShape.setPosition(topLeft + sf::Vector2f(0.f, size.y));
        myShape.setRotation(sf::degrees(-15));
    }
    else {
        myShape.setOrigin(size / 2.f);
        myShape.setPosition(topLeft + size / 2.f);
        myShape.setRotation(sf::degrees(0));
    }
}

void GameObject::update(float& dt) {

}

void GameObject::render() {
	if (myTextures != nullptr) {
		myShape.setTexture(myTextures);
		GameEngine::window->draw(myShape);
	}
    else if (hasColor) {
        myShape.setFillColor(color);
        GameEngine::window->draw(myShape);
    }
}
