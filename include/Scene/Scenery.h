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
protected:
    int numberOfFrames;
    int sequence;
    std::queue<std::string> frameNames;
    std::queue<Frame> frames;
    std::vector<Label> currentLabels;
    ResultsHandler resultsHandler;
    static inline int currentFrameNumber = 1;
    std::chrono::_V2::system_clock::time_point showingObjTimePoint;
public:

    Scenery(int pNumberOfFrames, int pSequence);

    virtual void processClicks(int x, int y) = 0;

    virtual void update() = 0;

    virtual void render() = 0;

    std::vector<KittiObject> getClickedObjects(int x, int y);

    void mouseEvents(int event, int x, int y, int flags, void *userdata);

    void keyEvents();

    const ResultsHandler &getResultsHandler() const;

    void loadFrames();


    const std::queue<Frame> &getFrames() const;

    void loadFrame(int frameNum, int sequence);

    const std::queue<std::string> &getFrameNames() const;

    void loadLabels(int sequence);

    int getSequence() const;
};


#endif //REACTIONGAME_SCENERY_H
