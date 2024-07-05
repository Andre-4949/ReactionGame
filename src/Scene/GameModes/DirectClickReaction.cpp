#include "../../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../../include/PreGameControlling/Game.h"

DirectClickReaction::DirectClickReaction(int pNumberOfFrames, int pSequence) :
        Scenery(pNumberOfFrames, pSequence) {
    Frame::labelFilter = {Labeltypes::CAR};
}

DirectClickReaction::~DirectClickReaction() {

}


void DirectClickReaction::processClicks(int x, int y) {
    if (frames.empty())return;

    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getObjects()[currentFrame.getRandomlySelectedObject()];

    randomObj.getLabel().getBoundingBox().setVisible(false);
    waitingOnClick = false;

    std::vector<KittiObject> clickedObjs = this->getClickedObjects(x, y);
    if (clickedObjs.empty()) {
        savePenaltyTime();
        return;
    }
    KittiObject clickedObj = clickedObjs.back();
    if (clickedObj == randomObj) {
        saveTime();
    }
}

void DirectClickReaction::makeRandomObjVisible() {
    Scenery::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 2);
    frames.front().getBoundingBoxOfRandomObject().setVisible(true);
}

void DirectClickReaction::setupFrame() {

}