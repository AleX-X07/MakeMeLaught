#pragma once
#include "SFML/Graphics.hpp"

class GameEngine;

class GameObject {
private:
	sf::RectangleShape myShape;
	sf::Texture* myTextures;
	sf::Vector2i mousePos;
	sf::Color color;
	bool hasColor;
public:

	GameObject(sf::Vector2f Pos, sf::Vector2f Size);
	~GameObject() = default;

	void setTextures(sf::Texture& texture);
	void setColor(sf::Color color);

	bool isClicked();
	bool isHover();
	void rotate(bool right, bool left);

	virtual void update(float& dt);
	virtual void render();
};

