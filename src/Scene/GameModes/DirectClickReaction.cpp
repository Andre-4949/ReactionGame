#include "../../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../../include/PreGameControlling/Game.h"

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
    Scenery::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
}

void DirectClickReaction::onPlayerMissedClick(int x, int y){
    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    savePenaltyTime();
    Scenery::showClickedPoint(x, y, cv::Scalar(0, 0, 255));
    Scenery::drawDistToCorrectBox(x, y, randomObj);
    render();
    Scenery::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
}


void DirectClickReaction::processClicks(int x, int y) {
    if (frames.empty() || !waitingOnClick)return;
    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    waitingOnClick = false;
    std::vector<KittiObject> clickedObjs = this->getClickedObjects(x, y);
    if (clickedObjs.empty()) {
        onPlayerMissedClick(x, y);
        return;
    }
    KittiObject clickedObj = clickedObjs.back();
    if (clickedObj == randomObj) {
        onPlayerClickedCorrect(x, y);
    }else{
        onPlayerMissedClick(x, y);
    }
}

void DirectClickReaction::makeRandomObjVisible() {
    Scenery::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 2);
    frames.front().getBoundingBoxOfRandomObject().setVisible(true);
}
