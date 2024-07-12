#include "GameSession.h"
#include <String>

#ifndef REACTIONGAME_MENU_H
#define REACTIONGAME_MENU_H

enum inputType {
    tSequence, tNumberOfFrames, tGameMode
};

class Menu {
private:
    int getIntInput(inputType t, int maxValue);

    std::string getStringInput();

    int numOfSequences = 21;

    int numOfGamemodes = 5;

public:
    GameSession getOptions();

    void printResults(ResultsHandler resultsHandler);
};


#endif //REACTIONGAME_MENU_H
