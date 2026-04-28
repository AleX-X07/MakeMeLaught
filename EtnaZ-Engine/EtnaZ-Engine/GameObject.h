#pragma once
#include "SFML/Graphics.hpp"

class GameEngine;

class GameObject {
private:
	sf::RectangleShape myShape;
	sf::Texture* myTextures;
public:
	GameObject(sf::Vector2f Pos, sf::Vector2f Size);
	~GameObject() = default;

	void setTextures(sf::Texture& texture);

	virtual void update(float& dt);
	virtual void render();
};

