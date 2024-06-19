//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_GAMESESSION_H
#define REACTIONGAME_GAMESESSION_H

#include <string>
#include "../sharedHelperClasses/Gamemode.h"
#include "../Scene/Scenery.h"
class GameSession {
private:
    bool gameSessionRunning = true;
    Gamemode mode;
//    Scenery scene;
    std::string name;
public:
    void loop();
    void render();
    void update();
    void mouseEvents(int event, int x, int y, int flags, void* userdata);
    void keyEvents();
};


#endif //REACTIONGAME_GAMESESSION_H
