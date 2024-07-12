
#include "../../../include/Scene/GameModes/SelectCarsReaction.h"

SelectCarsReaction::SelectCarsReaction(int pNumberOfFrames, int pSequence) : ColorChangeReaction(pNumberOfFrames,
                                                                                                 pSequence) {
    Frame::labelFilter = {Labeltypes::CAR, Labeltypes::DONTCARE, Labeltypes::VAN, Labeltypes::CYCLIST,
                          Labeltypes::PEDESTRIAN};
    this->defaultTimeToWaitForOneFrame = Constants::SECONDSTOMILLISECONDS * 60;
}

void SelectCarsReaction::processClicks(int x, int y) {
    if (frames.empty() || !waitingOnInput) return;
    std::vector<KittiObject> &selectedObjs = this->getClickedObjects(x, y);
    paintSolution(selectedObjs, x, y);
    ++this->sequence %= 20;
    showSolution();
}

void SelectCarsReaction::makeRandomObjVisible() {
    // keep empty to not call inherited
}



void SelectCarsReaction::showSolution() {
    render();
    waitMilliSeconds(1.5 * Constants::SECONDSTOMILLISECONDS);
    waitingOnInput = false;
}

void SelectCarsReaction::paintSolution(std::vector<KittiObject> selectedObjs, int clickedX, int clickedY) {
    if (selectedObjs.empty() || selectedObjs.back().getLabel().getMType() != Labeltypes::CAR) {
        SelectCarsReaction::onPlayerMissedClick(clickedX, clickedY);
    } else {
        SelectCarsReaction::onPlayerClickedCorrect(clickedX, clickedY);
    }

}

void SelectCarsReaction::onPlayerMissedClick(int x, int y) {
    savePenaltyTime();
    showClickedPoint(x, y, cv::Scalar(0, 0, 255));
    for(KittiObject obj: this->frames.front().getObjectsOfType(Labeltypes::CAR)){
        drawDistToCorrectBox(x, y, obj);
    }
    this->frames.front().colorObjectsOfType(Labeltypes::CAR, cv::Scalar(0, 0, 255));
}

void SelectCarsReaction::onPlayerClickedCorrect(int x, int y) {
    saveTime();

    showClickedPoint(x, y, cv::Scalar(0, 255, 0));
    if(frames.empty()) return;
    this->frames.front().colorObjectsOfType(Labeltypes::CAR, cv::Scalar(0, 255, 255));
    std::vector<KittiObject> &selectedObjs = this->getClickedObjects(x, y);
    KittiObject carToPaint = selectedObjs.back();
    for (KittiObject &item: this->frames.front().getObjects()) {
        if (item == carToPaint) {
            item.setColor(0, 255, 0);
            break;
        }
    }
}
