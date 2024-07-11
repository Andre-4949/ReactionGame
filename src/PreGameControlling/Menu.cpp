#include <filesystem>
#include "../../include/PreGameControlling/Menu.h"
#include "../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../include/Scene/GameModes/ColorChangeReaction.h"
#include "../../include/Scene/GameModes/EveryObjectReaction.h"
#include "../../include/Scene/GameModes/SelectCarsReaction.h"
#include "../../include/Scene/GameModes/ShrinkingBoxesReaction.h"


std::string Menu::getStringInput() {
    std::string output;
    std::cout << "Spielername eingeben: " << std::endl;
    std::cin >> output;
    std::cout << std::endl;
    return output;
}

bool isIntInputValid(int input, int max){
    if (input < 1 || input > max) return false;
    return true;
}

int Menu::getIntInput(inputType t, int maxValue) {
    int input;
    bool regularInput;
    switch (t) {
        case tSequence:
            std::cout << "Welche Bildsequenz moechtest du durchgehen? (1-" << maxValue << ")" << std::endl;
            break;
        case tNumberOfFrames:
            std::cout << "Wie viele Bilder moechtest du durchgehen? (maximal " << maxValue << ")" << std::endl;
            break;
        case tGameMode:
            std::cout
                    << "Welchen Spielmodus moechtest du spielen? (1-5) \n\t1: DirectClickReaction\n\t2: ColorChangeReaction\n\t3: ClickEverythingReaction\n\t4: SelectCarsReaction\n\t5: ShrinkingBoxesReaction"
                    << std::endl;
            break;
        default:
            break;
    }
    if(std::cin >> input){
        if (isIntInputValid(input, maxValue)){
            std::cout << std::endl;
            return input;
        }    
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl << "Unpassende Eingabe! Bitte noch einmal:" << std::endl;
    return getIntInput(t, maxValue);
}

GameSession Menu::getOptions() {
    std::string playerName = getStringInput();
    int sequence = getIntInput(tSequence, 21) - 1;

    auto dirIter = std::filesystem::directory_iterator(Scenery::generateImgFolderPathString(sequence));
    int fileCount = std::count_if(
    begin(dirIter),
    end(dirIter),
    [](auto& entry) { return entry.is_regular_file(); }
    );
    
    int numberOfFrames = getIntInput(tNumberOfFrames, fileCount);
    int gameMode = getIntInput(tGameMode, 5);
    Scenery *scene;
    switch (gameMode) {
        case 1:
            scene = new DirectClickReaction(numberOfFrames, sequence);
            break;
        case 2:
            scene = new ColorChangeReaction(numberOfFrames, sequence);
            break;
        case 3:
            scene = new EveryObjectReaction(numberOfFrames, sequence);
            break;
        case 4:
            scene = new SelectCarsReaction(numberOfFrames, sequence);
            break;
        case 5:
            scene = new ShrinkingBoxesReaction(numberOfFrames, sequence);
        default:
            break;
    }
    GameSession session(scene, playerName);
    return session;
}

void Menu::printResults(ResultsHandler resultsHandler) {
    resultsHandler.calcAvgTime();
    resultsHandler.calcBest3Times();
    resultsHandler.printResults();
}