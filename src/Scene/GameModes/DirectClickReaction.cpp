#include "../../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../../include/PreGameControlling/Game.h"
#include "../../../include/HelperClasses/Utils.h"

DirectClickReaction::DirectClickReaction(int pNumberOfFrames, int pSequence) :
        Scenery(pNumberOfFrames, pSequence) {
    Frame::labelFilter = {Labeltypes::CAR};
}

DirectClickReaction::~DirectClickReaction() {

}

void DirectClickReaction::onPlayerClickedCorrect(int x, int y){
    saveTime();
    Scenery::showClickedPoint(x, y, cv::Scalar(0, 255, 0));
    render();
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
}

void DirectClickReaction::onPlayerMissedClick(int x, int y){
    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    savePenaltyTime();
    Scenery::showClickedPoint(x, y, cv::Scalar(0, 0, 255));
    Scenery::drawDistToCorrectBox(x, y, randomObj);
    render();
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
}


void DirectClickReaction::processClicks(int x, int y) {
    //skip over function if user already clicked
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
