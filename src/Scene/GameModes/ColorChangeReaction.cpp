#include "../../../include/Scene/GameModes/ColorChangeReaction.h"
#include "../../../include/HelperClasses/Utils.h"
#include <random>


ColorChangeReaction::ColorChangeReaction(int pNumberOfFrames, int pSequence) : Scenery(pNumberOfFrames, pSequence) {
    Frame::labelFilter = {Labeltypes::CAR};
}

ColorChangeReaction::~ColorChangeReaction() {
}

void ColorChangeReaction::onPlayerMissedClick(int x, int y){
    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    savePenaltyTime();
    showClickedPoint(x, y, Constants::RED);
    drawDistToCorrectBox(x, clickedPoint.getY(), randomObj);
    render();
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
}

void ColorChangeReaction::onPlayerClickedCorrect(int x, int y){
    saveTime();
    showClickedPoint(x, y, Constants::GREEN);
    render();
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
}

void ColorChangeReaction::processSpaceBarInput() {
    //skip over function if user already clicked and pressed spacebar
    if (frames.empty() || !waitingOnInput)return;
    waitingOnInput = false;
    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    randomObj.setColor(Constants::BLUE);
    evaluateInput(selectedObjs, clickedPoint.getX(), clickedPoint.getY());
}

void ColorChangeReaction::processClicks(int x, int y) {
    if (frames.empty())
        return;
    selectedObjs = this->getClickedObjects(x, y);
    clickedPoint.setX(x);
    clickedPoint.setY(y);
    //wait 3 seconds for player to confirm input by pressing spacebar
    if ((char) cv::waitKey(3 * Constants::SECONDSTOMILLISECONDS) == ' ') {
        processSpaceBarInput();
        waitingOnInput = false;
    }
}


void ColorChangeReaction::makeRandomObjVisible() {
    //wait random time 1-2 seconds before drawin box around chosen object
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1 * Constants::SECONDSTOMILLISECONDS,
                                                                  2 * Constants::SECONDSTOMILLISECONDS);
    int random_milliseconds = dist(rng);
    Util::timing::waitMilliSeconds(random_milliseconds);
    frames.front().getBoundingBoxOfRandomObject().setColor(cv::Scalar(0, 0, 255));
}


void ColorChangeReaction::setupFrame() {
    this->frames.front().setAllKittiObjectsVisible();
    this->frames.front().setColorOfAllObjects(Constants::BLUE);
    Scenery::setupFrame();
}