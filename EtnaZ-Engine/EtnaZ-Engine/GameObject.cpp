#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject(sf::Vector2f Pos, sf::Vector2f Size){
	myTextures = nullptr;
    hasColor = false;
	myShape.setPosition(Pos);
	myShape.setSize(Size);


    hasHoverColor = false;  // NEW
    hasText = false;        // NEW
    myText = nullptr;       // NEW

    val = getRandomNumber(0,10);
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

// NEW
GameObject::~GameObject() {
    delete myText;
}

// NEW
void GameObject::setHoverColor(sf::Color _color) {
    hoverColor = _color;
    hasHoverColor = true;
}

void GameObject::setText(const std::string& str, sf::Font& font, int size) {
    if (!myText) myText = new sf::Text(font);
    myText->setString(str);
    myText->setCharacterSize(size);
    myText->setFillColor(sf::Color::White);

    // Centre le texte dans le shape
    sf::FloatRect textBounds = myText->getLocalBounds();
    sf::Vector2f shapePos = myShape.getPosition();
    sf::Vector2f shapeSize = myShape.getSize();
    myText->setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
                        textBounds.position.y + textBounds.size.y / 2.f });
    myText->setPosition({ shapePos.x + shapeSize.x / 2.f,
                          shapePos.y + shapeSize.y / 2.f });
    hasText = true;
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
    else if (hasColor || hasHoverColor) {  // ? seulement si il a une color
        if (hasHoverColor && isHover()) {
            myShape.setFillColor(hoverColor);
        }
        else if (hasColor) {
            myShape.setFillColor(color);
        }
        GameEngine::window->draw(myShape);
    }
    // sinon ? invisible, rien n'est draw

    if (hasText && myText) {
        GameEngine::window->draw(*myText);
    }
}
