//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_SCENERY_H
#define REACTIONGAME_SCENERY_H


#include <vector>
#include "Frame.h"
#include "KittiObject.h"
#include "ResultsHandler.h"
#include "queue"

class Scenery {
private:
    int numberOfFrames;
    int sequence;
    std::vector<std::string> frameNames;
    std::queue<Frame> frames;
    ResultsHandler resultsHandler;
    static inline int currentFrameNumber = 1;
public:

    Scenery(int pNumberOfFrames, int pSequence);

    virtual void processClicks() = 0;

    void render(cv::InputOutputArray &window);

    std::vector<KittiObject> getClickedObjects(int x, int y);

    void mouseEvents(int event, int x, int y, int flags, void *userdata);

    void keyEvents();

    const ResultsHandler &getResultsHandler() const;
    void loadFrames(int sequence);
};


#endif //REACTIONGAME_SCENERY_H
