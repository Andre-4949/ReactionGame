//
// Created by andre on 15.06.2024.
//

#include "GameSession.h"

#ifndef REACTIONGAME_GAME_H
#define REACTIONGAME_GAME_H


class Game {
public:
    static inline GameSession session = GameSession();

    void start();
};

#endif //REACTIONGAME_GAME_H
