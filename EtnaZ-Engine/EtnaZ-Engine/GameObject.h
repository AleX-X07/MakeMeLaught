#pragma once
#include "SFML/Graphics.hpp"
#include <random>

class GameEngine;

class GameObject {
private:
	sf::RectangleShape myShape;
	sf::Texture* myTextures;
	sf::Vector2i mousePos;
	sf::Color color;

	sf::Color hoverColor;        // NEW

	bool hasColor;
	int val;

	bool hasHoverColor;          // NEW
	bool hasText;                // NEW
	sf::Text* myText;            // NEW

public:

	GameObject(sf::Vector2f Pos, sf::Vector2f Size);
	~GameObject();

	void setTextures(sf::Texture& texture);
	void setColor(sf::Color color);

	bool isClicked();
	bool isHover();
	void rotate(bool right, bool left);

	void setHoverColor(sf::Color _color);
	void setText(const std::string& str, sf::Font& font, int size);

	int getRandomNumber(int min, int max);
	int getVal();

	virtual void update(float& dt);
	virtual void render();
};

