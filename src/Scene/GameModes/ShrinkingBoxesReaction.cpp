#include "../../../include/Scene/GameModes/ShrinkingBoxesReaction.h"

ShrinkingBoxesReaction::ShrinkingBoxesReaction(int pNumberOfFrames, int pSequence) : DirectClickReaction(
        pNumberOfFrames, pSequence) {
    lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
}

void setCopyAsNewImg(Frame& frame){
    cv::Mat imgCopy;
    frame.getOrigImg().copyTo(imgCopy);
    frame.setImg(imgCopy);
}

double getTimeDifference(std::chrono::_V2::system_clock::time_point later, std::chrono::_V2::system_clock::time_point earlier){
    using namespace std::chrono;
    double timeDifference = duration_cast<milliseconds>(later - earlier).count();
    return timeDifference;
}


void ShrinkingBoxesReaction::doWhileWaitingOnClick() {
    auto now = std::chrono::high_resolution_clock::now();
    double currentTimeDiff = getTimeDifference(now, lastShrinkedTimePoint);
    if (currentTimeDiff > (double) (Constants::SECONDSTOMILLISECONDS * shrinkingTimeDiff)) {
        lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
        Frame &currentFrame = frames.front();
        GTBoundingBox &boundingBoxOfRandomObj = currentFrame.getBoundingBoxOfRandomObject();
        currentFrame.getBoundingBoxOfRandomObject().moveTopLeft(this->deltaX, this->deltaY);
        currentFrame.getBoundingBoxOfRandomObject().moveBottomRight(-this->deltaX, -this->deltaY);
        currentFrame.setAllKittiObjectsInvisible();
        setCopyAsNewImg(currentFrame);
        currentFrame.getBoundingBoxOfRandomObject().setVisible(true);
        render();
    }
}

void ShrinkingBoxesReaction::makeRandomObjVisible() {
    DirectClickReaction::makeRandomObjVisible();
    initialRandomObjTopLeft = frames.front().getBoundingBoxOfRandomObject().getTopLeft();
    initialRandomObjBottomRight = frames.front().getBoundingBoxOfRandomObject().getBottomRight();

    double tempDeltaX, tempDeltaY;
    tempDeltaX = initialRandomObjBottomRight.getX() - initialRandomObjTopLeft.getX();
    tempDeltaX *= shrinkingTimeDiff;
    tempDeltaX /= 2 * ((double)defaultTimeToWaitForOneFrame / Constants::SECONDSTOMILLISECONDS);
    this->deltaX = (int) tempDeltaX;

    tempDeltaY = initialRandomObjBottomRight.getY() - initialRandomObjTopLeft.getY();
    tempDeltaY *= shrinkingTimeDiff;
    tempDeltaY /= 2 * ((double)defaultTimeToWaitForOneFrame / Constants::SECONDSTOMILLISECONDS);
    this->deltaY = (int)tempDeltaY;
}