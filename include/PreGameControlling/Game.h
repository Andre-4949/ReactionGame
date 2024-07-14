#ifndef REACTIONGAME_GAME_H
#define REACTIONGAME_GAME_H

#include "GameSession.h"

class Game {
    int argc;
    std::vector<std::string> argv;
public:
    static inline GameSession session = GameSession();

    void setupGameSession();

    Game(int argc, char* argv[]);

    void start();

    void parseGameSession();
};

#endif //REACTIONGAME_GAME_H
