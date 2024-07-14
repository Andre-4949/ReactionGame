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
    int numberOfFrames = 0;
    int defaultTimeToWaitForOneFrame = Constants::SECONDSTOMILLISECONDS * 3;
    int sequence = 0;
    std::queue<std::string> frameNames = {};
    std::queue<Frame> frames = {};
    std::unordered_map<int, std::vector<Label>> currentLabels = {};
    ResultsHandler resultsHandler;
    static inline int currentFrameNumber = 0;
    std::chrono::_V2::system_clock::time_point showingObjTimePoint;
    bool waitingOnInput = false;
    double penaltyTime = 5.0;
public:
    //neccesities
    Scenery(int pNumberOfFrames, int pSequence);

    virtual void update();

    void render();

    //frame-handling
    void loadFrames();

    void loadFrame(int frameNum);

    bool checkAllFramesShown();

    virtual void setupFrame();

    virtual void loadLabels();

    //input-handling
    virtual void processClicks(int x, int y) = 0;

    std::vector<KittiObject> &getClickedObjects(int x, int y);

    virtual void evaluateInput(std::vector<KittiObject> &objects, int x, int y);

    //drawing
    virtual void onPlayerMissedClick(int x, int y);

    virtual void onPlayerClickedCorrect(int x, int y);

    virtual void makeRandomObjVisible() = 0;

    void showClickedPoint(int x, int y, cv::Scalar color);

    void drawDistToCorrectBox(int x, int y, KittiObject correctObj);

    // other stuff 
    virtual void doWhileWaitingOnInput();

    void saveTime(double time = -1.0);

    //getters
    int getSequence() const;

    const std::queue<Frame> &getFrames() const;

    const std::queue<std::string> &getFrameNames() const;

    const ResultsHandler &getResultsHandler() const;
};


#endif //REACTIONGAME_SCENERY_H
