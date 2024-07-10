#include "../../../include/Scene/GameModes/ShrinkingBoxesReaction.h"

ShrinkingBoxesReaction::ShrinkingBoxesReaction(int pNumberOfFrames, int pSequence) : DirectClickReaction(pNumberOfFrames, pSequence) {
  lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
}

void ShrinkingBoxesReaction::doWhileWaitingOnClick(){
  //TODO Koordinaten von topleft und bottomright in abhängigkeit von currentTime/fulltime bestimmen -->Geradengleichung?

  double currentTimeDiff = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - lastShrinkedTimePoint).count();
  if(currentTimeDiff > (double)Constants::SECONDSTOMILLISECONDS * shrinkingTimeDiff){
    Frame& currentFrame = frames.front();
    KittiObject& randomObj = currentFrame.getRandomlySelectedObject();
    GTBoundingBox& randomObjBox = randomObj.getLabel().getBoundingBox();
    double boxShrinkingFactor = 0.5 * (Constants::SECONDSTOMILLISECONDS * shrinkingTimeDiff)/(double)defaultTimeToWaitForOneFrame;
    int boxCenterX = randomObjBox.getCenter().getX();
    int boxCenterY = randomObjBox.getCenter().getY();
    helper::Point currentTopLeft = randomObjBox.getTopLeft();
    helper::Point currentBottomRight = randomObjBox.getBottomRight();

    randomObjBox.setTopLeft(currentTopLeft.getX() + (int)std::round(boxShrinkingFactor * (boxCenterX - initialRandomObjTopLeft.getX())), currentTopLeft.getY() + (int)std::round(boxShrinkingFactor * (boxCenterY - initialRandomObjTopLeft.getY())));
    randomObjBox.setBottomRight(currentBottomRight.getX() + (int)std::round(boxShrinkingFactor * (boxCenterX - initialRandomObjBottomRight.getX())), currentBottomRight.getY() + (int)std::round(boxShrinkingFactor * (boxCenterY - initialRandomObjBottomRight.getY())));
    // currentTopLeft.move(std::round(boxShrinkingFactor * (initialRandomObjTopLeft.getX() + boxCenterX)), std::round(boxShrinkingFactor * (initialRandomObjTopLeft.getY() + boxCenterY)));
    // currentBottomRight.move(std::round(boxShrinkingFactor * (initialRandomObjBottomRight.getX() - boxCenterX)), std::round(boxShrinkingFactor * (initialRandomObjBottomRight.getY() - boxCenterY)));
    lastShrinkedTimePoint = std::chrono::high_resolution_clock::now();
    // randomObjBox.setVisible(true);


    cv::Mat imgCopy;
    currentFrame.getOrigImg().copyTo(imgCopy);
    currentFrame.setImg(imgCopy);
    currentFrame.setAllKittiObjectsInvisible();
    randomObjBox.setVisible(true);

    render();
  }
}

void ShrinkingBoxesReaction::makeRandomObjVisible(){
  DirectClickReaction::makeRandomObjVisible();
  initialRandomObjTopLeft = frames.front().getBoundingBoxOfRandomObject().getTopLeft();
  initialRandomObjBottomRight = frames.front().getBoundingBoxOfRandomObject().getBottomRight();
}