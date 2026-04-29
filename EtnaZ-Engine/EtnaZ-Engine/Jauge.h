#pragma once
#include "GameObject.h"
#include "Textures.h"

class Jauge : public GameObject {
private:
    sf::RectangleShape background;
    sf::RectangleShape fill;
    sf::Text* label;
    float maxWidth;
    float fillPercent; // 0.0 à 1.0

public:
    Jauge(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, const std::string& name, sf::Font& font);
    ~Jauge();

    void setFillPercent(float percent); // 0.0 à 1.0
    void increase(float amount);
    void decrease(float amount);

    virtual void update(float& dt) override;
    virtual void render() override;
};