#include "../../../include/Scene/GameModes/ColorChangeReaction.h"
#include <random>


ColorChangeReaction::ColorChangeReaction(int pNumberOfFrames, int pSequence) : Scenery(pNumberOfFrames, pSequence)
{
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
  if ((char)cv::waitKey(3000) == ' '){
    processSpaceBarInput();
    waitingOnClick = false;
  }
}


void ColorChangeReaction::makeRandomObjVisible(){
  std::random_device device;
  std::mt19937 rng(device());
  std::uniform_int_distribution<std::mt19937::result_type> dist(1000, 2000);
  int random_milliseconds = dist(rng);
  Scenery::waitMilliSeconds(random_milliseconds);
  frames.front().getBoundingBoxOfRandomObject().setColor(cv::Scalar(0, 0, 255));
}


void ColorChangeReaction::setupFrame(){
  this->frames.front().setAllKittiObjectVisible();
  this->frames.front().setColorOfAllObjects(cv::Scalar(255, 0, 0));
}