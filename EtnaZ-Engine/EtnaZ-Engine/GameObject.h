#pragma once
#include "SFML/Graphics.hpp"

class GameEngine;

class GameObject {
private:
	sf::RectangleShape myShape;
	sf::Texture* myTextures;
	sf::Vector2i mousePos;
	sf::Color* color;
	bool left;
	bool right;
public:
	bool rotate;

	GameObject(sf::Vector2f Pos, sf::Vector2f Size);
	~GameObject() = default;

	void setTextures(sf::Texture& texture);
	void setColor(sf::Color color);

	bool isClicked();
	bool isHover();
	void rotateRight();

	virtual void update(float& dt);
	virtual void render();
};

