
#include "../../../include/Scene/GameModes/SelectCarsReaction.h"
#include "../../../include/HelperClasses/Utils.h"

SelectCarsReaction::SelectCarsReaction(int pNumberOfFrames, int pSequence) : ColorChangeReaction(pNumberOfFrames,
                                                                                                 pSequence) {
    Frame::labelFilter = {Labeltypes::CAR, Labeltypes::DONTCARE, Labeltypes::VAN, Labeltypes::CYCLIST,
                          Labeltypes::PEDESTRIAN};
    this->defaultTimeToWaitForOneFrame = Constants::SECONDSTOMILLISECONDS * 60;
}

void SelectCarsReaction::processClicks(int x, int y) {
    if (frames.empty() || !waitingOnInput) return;
    std::vector<KittiObject> &selectedObjs = this->getClickedObjects(x, y);
    evaluateInput(selectedObjs, x, y);
    ++this->sequence %= 20;
    showSolution();
}

void SelectCarsReaction::makeRandomObjVisible() {
    // keep empty to not call inherited
}



void SelectCarsReaction::showSolution() {
    render();
    Util::timing::waitMilliSeconds(1.5 * Constants::SECONDSTOMILLISECONDS);
    waitingOnInput = false;
}

void SelectCarsReaction::evaluateInput(std::vector<KittiObject> &objects, int x, int y) {
    if (objects.empty() || objects.back().getLabel().getMType() != Labeltypes::CAR) {
        SelectCarsReaction::onPlayerMissedClick(x, y);
    } else {
        SelectCarsReaction::onPlayerClickedCorrect(x, y);
    }

}

void SelectCarsReaction::onPlayerMissedClick(int x, int y) {
    Frame &currentFrame = this->frames.front();
    savePenaltyTime();
    showClickedPoint(x, y, Constants::RED);
    for(KittiObject obj: currentFrame.getObjectsOfType(Labeltypes::CAR)){
        drawDistToCorrectBox(x, y, obj);
    }
    currentFrame.colorObjectsOfType(Labeltypes::CAR, Constants::RED);
}

void SelectCarsReaction::onPlayerClickedCorrect(int x, int y) {
    saveTime();
    showClickedPoint(x, y, Constants::GREEN);
    if(frames.empty()) return;
    Frame &currentFrame = this->frames.front();
    //color all cars yellow
    currentFrame.colorObjectsOfType(Labeltypes::CAR, Constants::YELLOW);
    std::vector<KittiObject> &selectedObjs = this->getClickedObjects(x, y);
    //color clicked car green
    KittiObject carToPaint = selectedObjs.back();
    for (KittiObject &item: currentFrame.getObjects()) {
        if (item == carToPaint) {
            item.setColor(0, 255, 0);
            break;
        }
    }
}
