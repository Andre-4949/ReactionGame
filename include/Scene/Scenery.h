#ifndef REACTIONGAME_SCENERY_H
#define REACTIONGAME_SCENERY_H

#include <vector>
#include "Frame.h"
#include "KittiObject.h"
#include "ResultsHandler.h"
#include "DrawHandler.h"
#include "queue"
#include "HelperClasses/Constants.h"

#include <chrono>
#include <unordered_map>

class Scenery {
protected:
    int numberOfFrames = 0;
    int defaultTimeToWaitForOneFrame = Constants::SECONDSTOMILLISECONDS * 3;
    int sequence = 0;
    std::queue<Frame> frames = {};
    std::unordered_map<int, std::vector<Label>> currentLabels = {};
    ResultsHandler resultsHandler;
    DrawHandler drawHandler;
    static inline int currentFrameNumber = 0;
    std::chrono::_V2::system_clock::time_point showingObjTimePoint;
    bool waitingOnInput = false;
    double penaltyTime = 5.0;
public:
    Scenery(int pNumberOfFrames, int pSequence);

    virtual void update();

    void render();

    virtual void makeRandomObjVisible() = 0;

    void loadFrames();

    void loadFrame(int frameNum);

    bool checkAllFramesShown();

    virtual void setupFrame();

    virtual void loadLabels();

    virtual void processClicks(int x, int y) = 0;

    std::vector<KittiObject> &getClickedObjects(int x, int y);

    virtual void evaluateInput(std::vector<KittiObject> &objects, int x, int y);

    virtual void doWhileWaitingOnInput();

    void saveTime(double time = -1);

    const std::queue<Frame> &getFrames() const;

    const ResultsHandler &getResultsHandler() const;

};


#endif //REACTIONGAME_SCENERY_H
