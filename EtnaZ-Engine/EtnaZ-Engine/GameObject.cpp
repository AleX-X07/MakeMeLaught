#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject(sf::Vector2f Pos, sf::Vector2f Size) {
    myTextures = nullptr;
    hasColor = false;
    myShape.setPosition(Pos);
    myShape.setSize(Size);

    hasHoverColor = false;
    hasText = false;
    myText = nullptr;
    textOffset = { 0.f, 0.f };

    // On stocke le vrai coin haut-gauche une fois pour toutes
    topLeftPos = Pos;

    val = getRandomNumber(0, 10);
    currentType = cardType::def;
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
        if (mousePos.x >= topLeftPos.x &&
            mousePos.x <= topLeftPos.x + myShape.getSize().x &&
            mousePos.y >= topLeftPos.y &&
            mousePos.y <= topLeftPos.y + myShape.getSize().y) {
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

GameObject::~GameObject() {
    delete myText;
}

void GameObject::setHoverColor(sf::Color _color) {
    hoverColor = _color;
    hasHoverColor = true;
}

// Repositionne le texte toujours depuis le vrai coin haut-gauche
void GameObject::updateTextPosition() {
    if (hasText && myText) {
        sf::Vector2f size = myShape.getSize();
        myText->setPosition({
            topLeftPos.x + size.x / 2.f + textOffset.x,
            topLeftPos.y + size.y / 2.f + textOffset.y
            });
    }
}

void GameObject::setText(const std::string& str, sf::Font& font, int size, sf::Color textColor, sf::Vector2f offset) {
    if (!myText) myText = new sf::Text(font);
    myText->setString(str);
    myText->setCharacterSize(size);
    myText->setFillColor(textColor);

    textOffset = offset;

    sf::FloatRect textBounds = myText->getLocalBounds();
    myText->setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
                        textBounds.position.y + textBounds.size.y / 2.f });

    hasText = true;
    updateTextPosition();
}

void GameObject::setCardType(cardType newType) {
    currentType = newType;
}

GameObject::cardType GameObject::getCardType() {
    return currentType;
}

void GameObject::rotate(bool right, bool left) {
    sf::Vector2f size = myShape.getSize();

    if (left) {
        myShape.setOrigin({ size.x, size.y });
        myShape.setPosition(topLeftPos + sf::Vector2f(size.x, size.y));
        myShape.setRotation(sf::degrees(15));
    }
    else if (right) {
        myShape.setOrigin({ 0.f, size.y });
        myShape.setPosition(topLeftPos + sf::Vector2f(0.f, size.y));
        myShape.setRotation(sf::degrees(-15));
    }
    else {
        myShape.setOrigin(size / 2.f);
        myShape.setPosition(topLeftPos + size / 2.f);
        myShape.setRotation(sf::degrees(0));
    }

    // Texte recalculé depuis topLeftPos : toujours correct quelle que soit la rotation
    updateTextPosition();
}

int GameObject::getRandomNumber(int min, int max) {
    std::random_device m_rd;
    std::mt19937 m_gen(m_rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(m_gen);
}

int GameObject::getVal() {
    return val;
}

void GameObject::update(float& dt) {

}

void GameObject::render() {
    if (myTextures != nullptr) {
        if (hasHoverColor && isHover()) {
            myShape.setFillColor(hoverColor);
        }
        else if (hasColor) {
            myShape.setFillColor(color);
        }
        myShape.setTexture(myTextures);
        GameEngine::window->draw(myShape);
    }
    else if (hasColor || hasHoverColor) {
        if (hasHoverColor && isHover()) {
            myShape.setFillColor(hoverColor);
        }
        else if (hasColor) {
            myShape.setFillColor(color);
        }
        GameEngine::window->draw(myShape);
    }

    if (hasText && myText) {
        if (currentType != cardType::def) {
            GameEngine::window->draw(*myText, myShape.getTransform());
        }
        else {
            GameEngine::window->draw(*myText);
        }
    }
}