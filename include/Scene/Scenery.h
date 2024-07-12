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

    Scenery(int pNumberOfFrames, int pSequence);

    virtual void processClicks(int x, int y) = 0;

    virtual void update();

    void render();

    std::vector<KittiObject> &getClickedObjects(int x, int y);

    void saveTime();

    void savePenaltyTime();

    const ResultsHandler &getResultsHandler() const;

    void loadFrames();


    const std::queue<Frame> &getFrames() const;

    void loadFrame(int frameNum);

    const std::queue<std::string> &getFrameNames() const;

    virtual void loadLabels();

    int getSequence() const;

    bool checkAllFramesShown();

    virtual void makeRandomObjVisible() = 0;

    virtual void setupFrame();

    void showClickedPoint(int x, int y, cv::Scalar color);

    void drawDistToCorrectBox(int x, int y, KittiObject correctObj);

    virtual void doWhileWaitingOnInput();

    virtual void onPlayerMissedClick(int x, int y) = 0;

    virtual void onPlayerClickedCorrect(int x, int y) = 0;

    virtual void evaluateInput(std::vector<KittiObject> &objects, int x, int y);
};


#endif //REACTIONGAME_SCENERY_H
