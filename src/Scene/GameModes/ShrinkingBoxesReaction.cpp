#include "../../../include/Scene/GameModes/ShrinkingBoxesReaction.h"
#include "../../../include/HelperClasses/Utils.h"

ShrinkingBoxesReaction::ShrinkingBoxesReaction(int pNumberOfFrames, int pSequence) : DirectClickReaction(
        pNumberOfFrames, pSequence) {
    lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
}

void ShrinkingBoxesReaction::setCopyAsNewImg(Frame& frame){
    cv::Mat imgCopy;
    frame.getOriginalImg().copyTo(imgCopy);
    frame.setImg(imgCopy);
    drawHandler.setImg(imgCopy);
    
}

void ShrinkingBoxesReaction::doWhileWaitingOnInput() {
    //calculate time since last shrinking tick --> decide if its time to shrink again
    auto now = std::chrono::high_resolution_clock::now();
    double currentTimeDiff = Util::timing::getTimeDifference(now, lastShrinkedTimePoint);
    if (currentTimeDiff > (double) (Constants::SECONDSTOMILLISECONDS * shrinkingTimeDiff)) {
        Frame &currentFrame = frames.front();
        GTBoundingBox &boundingBoxOfRandomObj = currentFrame.getBoundingBoxOfRandomObject();
        boundingBoxOfRandomObj.moveTopLeft(this->deltaX, this->deltaY);
        boundingBoxOfRandomObj.moveBottomRight(-(this->deltaX), -(this->deltaY));

        //can't erase box from img with opencv --> have to draw on a clear copy of current img
        currentFrame.setAllKittiObjectsInvisible();
        setCopyAsNewImg(currentFrame);
        boundingBoxOfRandomObj.setVisible(true);
        render();

        lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
    }
}


void ShrinkingBoxesReaction::calcDeltaX(){
    double tempDeltaX;
    // delta = starting width * (time between shrinks / total time)  
    //--> so that after the total time (-> after every shrink) the width becomes 0
    tempDeltaX = initialRandomObjBottomRight.getX() - initialRandomObjTopLeft.getX();
    tempDeltaX *= shrinkingTimeDiff;
    tempDeltaX /= 2 * ((double)defaultTimeToWaitForOneFrame / Constants::SECONDSTOMILLISECONDS); // /2 since border moves from both sides
    this->deltaX = (int) tempDeltaX;
}


void ShrinkingBoxesReaction::calcDeltaY(){
    double tempDeltaY;
    // delta = starting height * (time between shrinks / total time)  
    //--> so that after the total time (-> after every shrink) the height becomes 0
    tempDeltaY = initialRandomObjBottomRight.getY() - initialRandomObjTopLeft.getY();
    tempDeltaY *= shrinkingTimeDiff;
    tempDeltaY /= 2 * ((double)defaultTimeToWaitForOneFrame / Constants::SECONDSTOMILLISECONDS); // /2 since border moves from both sides
    this->deltaY = (int)tempDeltaY;
}


void ShrinkingBoxesReaction::makeRandomObjVisible() {
    DirectClickReaction::makeRandomObjVisible();

    initialRandomObjTopLeft = frames.front().getBoundingBoxOfRandomObject().getTopLeft();
    initialRandomObjBottomRight = frames.front().getBoundingBoxOfRandomObject().getBottomRight();

    calcDeltaX();
    calcDeltaY();
}