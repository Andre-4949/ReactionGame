#include "../../../include/Scene/GameModes/ColorChangeReaction.h"
ColorChangeReaction::ColorChangeReaction(int pNumberOfFrames, int pSequence) : Scenery(pNumberOfFrames, pSequence)
{
    Frame::labelFilter = {Labeltypes::CAR};
}

ColorChangeReaction::~ColorChangeReaction()
{
}

void ColorChangeReaction::processSpaceBarInput()
{
  if (frames.empty())
    return;

  waitingOnClick = false;

  Frame currentFrame = frames.front();
  KittiObject randomObj = currentFrame.getObjects()[currentFrame.getRandomlySelectedObject()];

  randomObj.setColor(cv::Scalar(255, 0, 0));

  if (selectedObjs.empty())
  {
    savePenaltyTime();
    return;
  }
  KittiObject clickedObj = selectedObjs.back();
  if (clickedObj == randomObj)
  {
    saveTime();
  }
  selectedObjs.clear();
}

void ColorChangeReaction::processClicks(int x, int y)
{
  if (frames.empty())
    return;

  selectedObjs = this->getClickedObjects(x, y);
}


void ColorChangeReaction::makeRandomObjVisible(){
  frames.front().getBoundingBoxOfRandomObject().setColor(cv::Scalar(0, 0, 255));
}


void ColorChangeReaction::setupFrame(){
    this->frames.front().setAllKittiObjectVisible();
    this->frames.front().setColorOfAllObjects(cv::Scalar(255, 0, 0));
}