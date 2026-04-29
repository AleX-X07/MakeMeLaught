#pragma once
#include "SFML/Graphics.hpp"
#include <random>

class GameEngine;

class GameObject {
public:

	enum class cardType {
		def,
		soft,
		beauf,
		noir,
	};

private:
	sf::RectangleShape myShape;
	sf::Texture* myTextures;
	sf::Vector2i mousePos;
	sf::Color color;
	sf::Color hoverColor;

	bool hasColor;
	int val;

	bool hasHoverColor;
	bool hasText;
	sf::Text* myText;
	sf::Vector2f textOffset;  // offset par rapport au centre du shape
	sf::Vector2f topLeftPos;  // vrai coin haut-gauche, jamais modifié par rotate()

	cardType currentType;

	void updateTextPosition(); // recalcule la position du texte depuis topLeftPos

public:

	GameObject(sf::Vector2f Pos, sf::Vector2f Size);
	~GameObject();

	void setTextures(sf::Texture& texture);
	void setColor(sf::Color color);

	bool isClicked();
	bool isHover();
	void rotate(bool right, bool left);

	void setHoverColor(sf::Color _color);
	void setText(const std::string& str, sf::Font& font, int size, sf::Color textColor = sf::Color::White, sf::Vector2f offset = { 0.f, 0.f });

	void setCardType(cardType newType);
	cardType getCardType();

	static int getRandomNumber(int min, int max);
	int getVal();

	virtual void update(float& dt);
	virtual void render();
};