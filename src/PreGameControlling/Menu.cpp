#include <filesystem>
#include "../../include/PreGameControlling/Menu.h"
#include "../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../include/Scene/GameModes/ColorChangeReaction.h"
#include "../../include/Scene/GameModes/EveryObjectReaction.h"
#include "../../include/Scene/GameModes/SelectCarsReaction.h"
#include "../../include/Scene/GameModes/ShrinkingBoxesReaction.h"
#include "../../include/HelperClasses/Utils.h"

Menu::Menu(){
    
}

std::string Menu::getStringInput() {
    std::string output;
    std::cout << "Spielername eingeben: " << std::endl;
    std::cin >> output;
    std::cout << std::endl;
    return output;
}

bool isIntInputValid(int input, int max) {
    if (input < 1 || input > max) return false;
    return true;
}

void printOptionsOutput(inputType t, int maxValue) {
    //int value of corresponding enum --> index of vector
    std::vector<std::string> outputByInputType =
            {
                    "Welche Bildsequenz moechtest du durchgehen? (1-" + std::to_string(maxValue) + ")",
                    "Wie viele Bilder moechtest du durchgehen? (bis zu " + std::to_string(maxValue) + ")",
                    "Welchen Spielmodus moechtest du spielen? (1-" + std::to_string(maxValue) +
                    ") \n\t1: DirectClickReaction\n\t2: ColorChangeReaction\n\t3: ClickEverythingReaction\n\t4: SelectCarsReaction\n\t5: ShrinkingBoxesReaction"
            };
    std::cout << outputByInputType[t] << std::endl;
}

int Menu::getIntInput(inputType t, int maxValue) {
    int input;
    bool regularInput;
    printOptionsOutput(t, maxValue);
    //is false if user inputs non-int
    if (std::cin >> input) {
        if (isIntInputValid(input, maxValue)) {
            std::cout << std::endl;
            return input;
        }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl << "Unpassende Eingabe! Bitte noch einmal:" << std::endl;
    return getIntInput(t, maxValue);
}


Scenery *Menu::getGameModeByUserInput(int gamemodeNum, int numberOfFrames, int sequence) {
    Scenery *scene;
    switch (gamemodeNum) {
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
            break;
        default:
            // std::cout << "No gamemode could be chosen by the given inputs. Try to use values between 1 and 5." << std::endl;
            exit(0);
            break;
    }
    return scene;
}

GameSession Menu::getOptions() {
    std::string playerName = getStringInput();

    // sequence - 1, since it later serves as an index --> minimum is 0
    int sequence = getIntInput(tSequence, numOfSequences) - 1;
    int fileCount = Util::fileUtil::getAmountOfFilesInFolder(Util::fileUtil::generateImgFolderPathString(sequence));
    int numberOfFrames = getIntInput(tNumberOfFrames, fileCount);
    int gameMode = getIntInput(tGameMode, numOfGamemodes);
    Scenery *scene = Menu::getGameModeByUserInput(gameMode, numberOfFrames, sequence);
    GameSession session(scene, playerName);
    return session;
}

void Menu::printResults(ResultsHandler resultsHandler) {
    resultsHandler.calcAvgTime();
    resultsHandler.calcBest3Times();
    resultsHandler.printResults();
}