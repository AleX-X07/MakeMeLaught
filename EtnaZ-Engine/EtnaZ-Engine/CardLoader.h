#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

// Structure pour stocker une blague avec son type
struct CardData {
    GameObject::cardType type;
    std::string text;
};

class CardLoader {
public:
    // Lit le fichier et retourne un vecteur de CardData
    static std::vector<CardData> loadFromFile(const std::string& filePath);
};