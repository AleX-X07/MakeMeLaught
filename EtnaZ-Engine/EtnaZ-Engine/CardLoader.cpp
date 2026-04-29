#include "CardLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<CardData> CardLoader::loadFromFile(const std::string& filePath) {
    std::vector<CardData> cards;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "[CardLoader] Impossible d'ouvrir le fichier : " << filePath << std::endl;
        return cards;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Ignore les lignes vides
        if (line.empty()) continue;

        // Sépare sur le '|'
        size_t sep = line.find('|');
        if (sep == std::string::npos) {
            std::cerr << "[CardLoader] Ligne ignorée (pas de '|') : " << line << std::endl;
            continue;
        }

        // Récupère et nettoie le type
        std::string typeStr = line.substr(0, sep);
        while (!typeStr.empty() && typeStr.back() == ' ') typeStr.pop_back();
        while (!typeStr.empty() && typeStr.front() == ' ') typeStr.erase(typeStr.begin());

        // Récupère et nettoie le texte (enlève espaces et guillemets)
        std::string text = line.substr(sep + 1);
        while (!text.empty() && (text.front() == ' ' || text.front() == '"')) text.erase(text.begin());
        while (!text.empty() && (text.back() == ' ' || text.back() == '"')) text.pop_back();

        if (text.empty()) {
            std::cerr << "[CardLoader] Ligne ignorée (texte vide) : " << line << std::endl;
            continue;
        }

        // Convertit le type
        GameObject::cardType type;
        if (typeStr == "soft")  type = GameObject::cardType::soft;
        else if (typeStr == "noir")  type = GameObject::cardType::noir;
        else if (typeStr == "beauf") type = GameObject::cardType::beauf;
        else {
            std::cerr << "[CardLoader] Type inconnu '" << typeStr << "' : " << line << std::endl;
            continue;
        }

        cards.push_back({ type, text });
    }

    std::cout << "[CardLoader] " << cards.size() << " blagues chargées depuis " << filePath << std::endl;
    return cards;
}