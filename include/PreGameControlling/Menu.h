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

    std::string getStringInput() ;

    const int numOfGamemodes = 5;

    static const int numOfSequences = 21;

public:
    Menu();
    
    GameSession readOptions();

    static GameMode* getGameModeByUserInput(const int gamemodeNum, const int numberOfFrames, const int sequence);

    static void printResults(ResultsHandler resultsHandler);

};


#endif //REACTIONGAME_MENU_H
