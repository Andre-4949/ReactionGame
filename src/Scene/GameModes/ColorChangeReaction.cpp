#include "../../../include/Scene/GameModes/ColorChangeReaction.h"
#include <random>


ColorChangeReaction::ColorChangeReaction(int pNumberOfFrames, int pSequence) : Scenery(pNumberOfFrames, pSequence) {
    Frame::labelFilter = {Labeltypes::CAR};
}

ColorChangeReaction::~ColorChangeReaction() {
}

void ColorChangeReaction::processSpaceBarInput() {
    if (frames.empty() || !waitingOnClick)return;

    waitingOnClick = false;

    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    randomObj.setColor(cv::Scalar(255,0,0));

    if (selectedObjs.empty()) {
        savePenaltyTime();
        showClickedPoint(clickedPoint.getX(), clickedPoint.getY(), cv::Scalar(0, 0, 255));
        drawDistToCorrectBox(clickedPoint.getX(), clickedPoint.getY(), randomObj);
        render();
        Scenery::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
        return;
    }
    KittiObject clickedObj = selectedObjs.back();
    if (clickedObj == randomObj) {
        saveTime();
        showClickedPoint(clickedPoint.getX(), clickedPoint.getY(), cv::Scalar(0, 255, 0));
        render();
        Scenery::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
    }else{
        savePenaltyTime();
        showClickedPoint(clickedPoint.getX(), clickedPoint.getY(), cv::Scalar(0, 0, 255));
        drawDistToCorrectBox(clickedPoint.getX(), clickedPoint.getY(), randomObj);
        render();
        Scenery::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
    }
    selectedObjs.clear();
}

void ColorChangeReaction::processClicks(int x, int y) {
    if (frames.empty())
        return;
    selectedObjs = this->getClickedObjects(x, y);
    clickedPoint.setX(x);
    clickedPoint.setY(y);
    if ((char) cv::waitKey(3 * Constants::SECONDSTOMILLISECONDS) == ' ') {
        processSpaceBarInput();
        waitingOnClick = false;
    }
}


void ColorChangeReaction::makeRandomObjVisible() {
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1 * Constants::SECONDSTOMILLISECONDS,
                                                                  2 * Constants::SECONDSTOMILLISECONDS);
    int random_milliseconds = dist(rng);
    Scenery::waitMilliSeconds(random_milliseconds);
    frames.front().getBoundingBoxOfRandomObject().setColor(cv::Scalar(0, 0, 255));
}


void ColorChangeReaction::setupFrame() {
    this->frames.front().setAllKittiObjectsVisible();
    this->frames.front().setColorOfAllObjects(cv::Scalar(255, 0, 0));
}