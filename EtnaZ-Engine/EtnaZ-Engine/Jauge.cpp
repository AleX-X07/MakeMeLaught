#include "Jauge.h"
#include "GameEngine.h"

Jauge::Jauge(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, const std::string& name, sf::Font& font)
    : GameObject(pos, size)
{
    fillPercent = 0.f;
    maxWidth = size.x;

    // Fond gris foncé
    background.setPosition(pos);
    background.setSize(size);
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2.f);

    // Barre de remplissage
    fill.setPosition(pos);
    fill.setSize({ 0.f, size.y });
    fill.setFillColor(fillColor);

    // Label
    label = new sf::Text(font);
    label->setString(name);
    label->setCharacterSize(22);
    label->setFillColor(sf::Color::White);

    sf::FloatRect tb = label->getLocalBounds();
    label->setOrigin({ tb.position.x + tb.size.x / 2.f, tb.position.y + tb.size.y / 2.f });
    label->setPosition({ pos.x + size.x / 2.f, pos.y - 20.f });
}

Jauge::~Jauge() {
    delete label;
}

void Jauge::setFillPercent(float percent) {
    fillPercent = std::clamp(percent, 0.f, 1.f);
    fill.setSize({ maxWidth * fillPercent, fill.getSize().y });
}

void Jauge::increase(float amount) {
    setFillPercent(fillPercent + amount);
}

void Jauge::decrease(float amount) {
    setFillPercent(fillPercent - amount);
}

void Jauge::update(float& dt) {}

void Jauge::render() {
    GameEngine::window->draw(background);
    GameEngine::window->draw(fill);
    //GameEngine::window->draw(*label);
}