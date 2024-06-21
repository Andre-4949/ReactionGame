//
// Created by andre on 15.06.2024.
//

#include "GameSession.h"
#include <String>
#ifndef REACTIONGAME_MENU_H
#define REACTIONGAME_MENU_H

enum inputType{tNumberOfFrames, tSequence, tGameMode};

class Menu {
  private:
    int getIntInput(inputType t);
    std::string getStringInput();
  public:
    GameSession getOptions();
    void printResults(ResultsHandler resultsHandler);
};


#endif //REACTIONGAME_MENU_H
