#ifndef REACTIONGAME_MENU_H
#define REACTIONGAME_MENU_H

#include "GameSession.h"
#include <string>

enum inputType {
    tSequence, tNumberOfFrames, tGameMode
};

class Menu {
private:
    int getIntInput(inputType t, int maxValue);

    std::string getStringInput();

    int numOfGamemodes = 5;

public:
    Menu();
    
    static inline const int numOfSequences = 21;

    GameSession getOptions();

    static Scenery* getGameModeByUserInput(int gamemodeNum, int numberOfFrames, int sequence);

    static void printResults(ResultsHandler resultsHandler);

};


#endif //REACTIONGAME_MENU_H
