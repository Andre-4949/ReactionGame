#ifndef REACTIONGAME_SCENERY_H
#define REACTIONGAME_SCENERY_H


#include <vector>
#include "Frame.h"
#include "KittiObject.h"
#include "ResultsHandler.h"
#include "queue"
#include "HelperClasses/Constants.h"

#include <chrono>
#include <unordered_map>

class Scenery {
protected:
    int numberOfFrames;
    int defaultTimeToWaitForOneFrame = Constants::SECONDSTOMILLISECONDS * 3;
    int sequence;
    std::queue<std::string> frameNames;
    std::queue<Frame> frames;
    std::unordered_map<int, std::vector<Label>> currentLabels;
    ResultsHandler resultsHandler;
    static inline int currentFrameNumber = 0;
    std::chrono::_V2::system_clock::time_point showingObjTimePoint;
    bool waitingOnClick = false;
public:

    Scenery(int pNumberOfFrames, int pSequence);

    virtual void processClicks(int x, int y) = 0;

    virtual void update();

    void render();

    std::vector<KittiObject> &getClickedObjects(int x, int y);

    void mouseEvents(int event, int x, int y, int flags, void *userdata);

    void keyEvents();

    void saveTime();

    void savePenaltyTime();

    const ResultsHandler &getResultsHandler() const;

    void loadFrames();


    const std::queue<Frame> &getFrames() const;

    void loadFrame(int frameNum, int sequence);

    const std::queue<std::string> &getFrameNames() const;

    virtual void loadLabels(int sequence);

    int getSequence() const;

    bool checkAllFramesShown();

    virtual void makeRandomObjVisible() = 0;

    virtual void setupFrame() = 0;

    void waitMilliSeconds(int time, std::function<bool(void)> breakCondition = []() { return false; }, std::function<void(void)> doWhileWaiting = [](){});

    void showClickedPoint(int x, int y, cv::Scalar color);

    void drawDistToCorrectBox(int x, int y, KittiObject correctObj);

    virtual void doWhileWaitingOnClick();
};


#endif //REACTIONGAME_SCENERY_H
