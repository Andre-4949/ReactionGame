#ifndef REACTIONGAME_GAME_H
#define REACTIONGAME_GAME_H

#include "GameSession.h"

class Game {
    int argc;
    std::vector<std::string> argv;
    void setupGameSession()const;
    void parseGameSession()const;
public:
    static inline GameSession session = GameSession();

    Game(const int argc, const char* argv[]);

    void start();

};

#endif //REACTIONGAME_GAME_H
