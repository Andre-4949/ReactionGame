#include "GameSession.h"

#ifndef REACTIONGAME_GAME_H
#define REACTIONGAME_GAME_H


class Game {
public:
    static inline GameSession session = GameSession();

    void start();
};

#endif //REACTIONGAME_GAME_H
