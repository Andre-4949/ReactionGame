
#ifndef REACTIONGAME_GAMESESSION_H
#define REACTIONGAME_GAMESESSION_H

#include <string>
#include "../Scene/Scenery.h"

class GameSession {
private:
    bool gameSessionRunning = true;
    Scenery *scene;
    std::string name;
    std::string windowName = "ReactionGame";
public:
    GameSession() {};

    GameSession(Scenery *pScene, std::string pName);

    void loop();

    void render();

    void update();

    void mouseEvents(int event, int x, int y, int flags, void *userdata);

    Scenery *getScene();

    const std::string &getWindowName() const;

    void setWindowName(const std::string &windowName);

    const cv::Mat &getCurrentImage() const;

    void setCurrentImage(const cv::Mat &currentImage);

    void setGameSessionRunning(bool gameSessionRunning);
};


#endif //REACTIONGAME_GAMESESSION_H
