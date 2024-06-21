//
// Created by andre on 15.06.2024.
//

#include "GameSession.h"
#ifndef REACTIONGAME_MENU_H
#define REACTIONGAME_MENU_H


class Menu {
  public:
    GameSession getOptions();
    int getInput();
    void printResults();
};


#endif //REACTIONGAME_MENU_H
