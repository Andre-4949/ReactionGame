
#ifndef REACTIONGAME_GAMESESSION_H
#define REACTIONGAME_GAMESESSION_H

#include <string>
#include "../Scene/GameMode.h"

class GameSession {
private:
    bool gameSessionRunning = true;
    GameMode *scene = nullptr;
    std::string name;
    std::string windowName = "ReactionGame";
public:
    GameSession() = default;

    GameSession(GameMode *pScene, std::string pName);

    void loop();

    void render();

    void update();

    void mouseEvents(int event, int x, int y, int flags, void *userdata);

    GameMode *getScene();

    const std::string &getWindowName();

    const cv::Mat &getCurrentImg();

    void setCurrentImage(cv::Mat &currentImage);

    void setGameSessionRunning(bool gameSessionRunning);
};


#endif //REACTIONGAME_GAMESESSION_H
