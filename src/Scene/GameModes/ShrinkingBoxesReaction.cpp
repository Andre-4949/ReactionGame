#include "../../../include/Scene/GameModes/ShrinkingBoxesReaction.h"

ShrinkingBoxesReaction::ShrinkingBoxesReaction(int pNumberOfFrames, int pSequence) : DirectClickReaction(
        pNumberOfFrames, pSequence) {
    lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
}

void ShrinkingBoxesReaction::doWhileWaitingOnClick() {
    double currentTimeDiff = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - lastShrinkedTimePoint).count();
    if (currentTimeDiff > (double) (Constants::SECONDSTOMILLISECONDS * shrinkingTimeDiff)) {
        Frame &currentFrame = frames.front();
        frames.front().getBoundingBoxOfRandomObject().moveTopLeft(this->deltaX, this->deltaY);
        frames.front().getBoundingBoxOfRandomObject().moveBottomRight(-this->deltaX, -this->deltaY);
        lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
        currentFrame.setAllKittiObjectsInvisible();

        cv::Mat imgCopy;
        currentFrame.getOrigImg().copyTo(imgCopy);
        currentFrame.setImg(imgCopy);
        frames.front().getBoundingBoxOfRandomObject().setVisible(true);

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