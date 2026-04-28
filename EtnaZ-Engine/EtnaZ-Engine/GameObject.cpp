#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject(sf::Vector2f Pos, sf::Vector2f Size){
	myTextures = nullptr;
	myShape.setPosition(Pos);
	myShape.setSize(Size);
}

void GameObject::setTextures(sf::Texture& texture) {
	myTextures = &texture;
}

void GameObject::update(float& dt) {

}

void GameObject::render() {
	if (!myTextures) {
		GameEngine::window->draw(myShape);
	}
	else {
		myShape.setFillColor(sf::Color::White);
		GameEngine::window->draw(myShape);
	}
}
