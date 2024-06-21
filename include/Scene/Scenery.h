//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_SCENERY_H
#define REACTIONGAME_SCENERY_H


#include <vector>
#include "Frame.h"
#include "KittiObject.h"
#include "ResultsHandler.h"

class Scenery {
private:
    int numberOfFrames;
    std::vector<Frame> frameNames;
public:
    Scenery(int pNumberOfFrames);

    ResultsHandler resultsHandler;

    virtual void processClicks() = 0;

    void render();

    std::vector<KittiObject> getClickedObjects(int x, int y);
    void mouseEvents(int event, int x, int y, int flags, void* userdata);
    void keyEvents();
};


#endif //REACTIONGAME_SCENERY_H
