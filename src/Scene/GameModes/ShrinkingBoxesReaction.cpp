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




void ShrinkingBoxesReaction::doWhileWaitingOnInput() {
    //calculate time since last shrinking tick --> decide if its time again
    auto now = std::chrono::high_resolution_clock::now();
    double currentTimeDiff = Scenery::getTimeDifference(now, lastShrinkedTimePoint);
    if (currentTimeDiff > (double) (Constants::SECONDSTOMILLISECONDS * shrinkingTimeDiff)) {
        Frame &currentFrame = frames.front();
        GTBoundingBox &boundingBoxOfRandomObj = currentFrame.getBoundingBoxOfRandomObject();
        boundingBoxOfRandomObj.moveTopLeft(this->deltaX, this->deltaY);
        boundingBoxOfRandomObj.moveBottomRight(-(this->deltaX), -(this->deltaY));
        currentFrame.setAllKittiObjectsInvisible();
        setCopyAsNewImg(currentFrame);
        boundingBoxOfRandomObj.setVisible(true);
        render();
        lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
    }
}


void ShrinkingBoxesReaction::calcDeltaX(){
    double tempDeltaX;
    tempDeltaX = initialRandomObjBottomRight.getX() - initialRandomObjTopLeft.getX();
    tempDeltaX *= shrinkingTimeDiff;
    tempDeltaX /= 2 * ((double)defaultTimeToWaitForOneFrame / Constants::SECONDSTOMILLISECONDS);
    this->deltaX = (int) tempDeltaX;
}


void ShrinkingBoxesReaction::calcDeltaY(){
    double tempDeltaY;
    tempDeltaY = initialRandomObjBottomRight.getY() - initialRandomObjTopLeft.getY();
    tempDeltaY *= shrinkingTimeDiff;
    tempDeltaY /= 2 * ((double)defaultTimeToWaitForOneFrame / Constants::SECONDSTOMILLISECONDS);
    this->deltaY = (int)tempDeltaY;
}


void ShrinkingBoxesReaction::makeRandomObjVisible() {
    DirectClickReaction::makeRandomObjVisible();

    initialRandomObjTopLeft = frames.front().getBoundingBoxOfRandomObject().getTopLeft();
    initialRandomObjBottomRight = frames.front().getBoundingBoxOfRandomObject().getBottomRight();

    calcDeltaX();
    calcDeltaY();
}