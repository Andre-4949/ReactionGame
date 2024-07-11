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

void printOptionsOutput(inputType t, int maxValue){
std::vector<std::string> outputByInputType = 
    {
        "Welche Bildsequenz moechtest du durchgehen? (1-" + std::to_string(maxValue) + ")",
        "Wie viele Bilder moechtest du durchgehen? (bis zu " + std::to_string(maxValue) + ")",
        "Welchen Spielmodus moechtest du spielen? (1-" + std::to_string(maxValue) + ") \n\t1: DirectClickReaction\n\t2: ColorChangeReaction\n\t3: ClickEverythingReaction\n\t4: SelectCarsReaction\n\t5: ShrinkingBoxesReaction"
    };
    std::cout << outputByInputType[t] << std::endl;
}

int Menu::getIntInput(inputType t, int maxValue) {
    int input;
    bool regularInput;
    printOptionsOutput(t, maxValue);
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

int getAmountOfFilesInFolder(std::string folderPath){
    auto dirIter = std::filesystem::directory_iterator(folderPath);
    int fileCount = std::count_if(
    dirIter,
    {},
    [](auto& entry) { return entry.is_regular_file(); }
    );
    return fileCount;
}

Scenery* getGameModeByUserInput(int input, int numberOfFrames, int sequence){
    Scenery* scene;
    switch (input) {
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
    return scene;
}

GameSession Menu::getOptions() {
    std::string playerName = getStringInput();
    int sequence = getIntInput(tSequence, 21) - 1;

    int fileCount = getAmountOfFilesInFolder(Scenery::generateImgFolderPathString(sequence));

    int numberOfFrames = getIntInput(tNumberOfFrames, fileCount);
    int gameMode = getIntInput(tGameMode, 5);
    Scenery *scene;
    scene = getGameModeByUserInput(gameMode, numberOfFrames, sequence);
    GameSession session(scene, playerName);
    return session;
}

void Menu::printResults(ResultsHandler resultsHandler) {
    resultsHandler.calcAvgTime();
    resultsHandler.calcBest3Times();
    resultsHandler.printResults();
}