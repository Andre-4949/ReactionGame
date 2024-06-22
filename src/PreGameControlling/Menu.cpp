//
// Created by andre on 15.06.2024.
//
#include "../../include/PreGameControlling/Menu.h"
#include "../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../include/Scene/GameModes/ColorChangeReaction.h"

std::string Menu::getStringInput() {
    std::string output;
    std::cout << "Spielername eingeben: " << std::endl;
    std::cin >> output;
    std::cout << std::endl;
    return output;
}

int Menu::getIntInput(inputType t) {
    int output;
    switch (t) {
        case tNumberOfFrames:
            std::cout << "Wieviele Bilder moechtest du durchgehen?" << std::endl;
            break;

        case tSequence:
            std::cout << "Welche Bildsequenz moechtest du durchgehen?" << std::endl;
            break;
        case tGameMode:
            std::cout << "Welchen Spielmodus moechtest du spielen? (1 oder 2)" << std::endl;
            break;
        default:
            break;
    }
    std::cin >> output;
    std::cout << std::endl;
    return output;
}

GameSession Menu::getOptions() {
    std::string playerName = getStringInput();
    int numberOfFrames = getIntInput(tNumberOfFrames);
    int sequence = getIntInput(tSequence);
    int gameMode = getIntInput(tGameMode);
    Scenery *scene;
    switch (gameMode) {
        case 1:
            scene = new DirectClickReaction(numberOfFrames);
            break;
        case 2:
            scene = new ColorChangeReaction(numberOfFrames);
        default:
            break;
    }
    GameSession session((Gamemode) gameMode, scene, playerName);
    return session;
}

void Menu::printResults(ResultsHandler resultsHandler) {
    resultsHandler.calcAvgTime();
    resultsHandler.calcBest3Times();
    resultsHandler.printResults();
}
