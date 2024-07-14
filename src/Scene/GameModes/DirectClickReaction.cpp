#include "../../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../../include/PreGameControlling/Game.h"
#include "../../../include/HelperClasses/Utils.h"

DirectClickReaction::DirectClickReaction(int pNumberOfFrames, int pSequence) :
        Scenery(pNumberOfFrames, pSequence) {
    Frame::labelFilter = {Labeltypes::CAR};
}

DirectClickReaction::~DirectClickReaction() {

}

void DirectClickReaction::processClicks(int x, int y) {
    //skip over function if user already clicked --> !waitingOnInput
    if (frames.empty() || !waitingOnInput)return;
    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    waitingOnInput = false;
    std::vector<KittiObject> clickedObjs = this->getClickedObjects(x, y);
    evaluateInput(clickedObjs, x, y);

}

void DirectClickReaction::makeRandomObjVisible() {
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 2);
    frames.front().getBoundingBoxOfRandomObject().setVisible(true);
}
