//
// Created by andre on 05.07.2024.
//

#include "../../../include/Scene/GameModes/SelectCarsReaction.h"

SelectCarsReaction::SelectCarsReaction(int pNumberOfFrames, int pSequence) : ColorChangeReaction(pNumberOfFrames,
                                                                                                 pSequence) {
    Frame::labelFilter = {Labeltypes::CAR, Labeltypes::DONTCARE, Labeltypes::VAN, Labeltypes::CYCLIST,
                          Labeltypes::PEDESTRIAN};
    this->defaultTimeToWaitForOneFrame = Constants::SECONDSTOMILLISECONDS * 60;
}

void SelectCarsReaction::processClicks(int x, int y) {
    if (frames.empty() || !waitingOnClick) return;
    std::vector<KittiObject> &selectedObjs = this->getClickedObjects(x, y);
    paintSolution(selectedObjs, x, y);
    ++this->sequence %= 20;
    showSolution();
}

void SelectCarsReaction::makeRandomObjVisible() {
    // keep empty to not call inherited
}

void SelectCarsReaction::loadLabels(int sequence) {
    Scenery::loadLabels(sequence);
}

void SelectCarsReaction::showSolution() {
    render();
    waitMilliSeconds(1.5 * Constants::SECONDSTOMILLISECONDS);
    waitingOnClick = false;
}

void SelectCarsReaction::paintSolution(std::vector<KittiObject> selectedObjs, int clickedX, int clickedY) {
    if (selectedObjs.empty() || selectedObjs.back().getLabel().getMType() != Labeltypes::CAR) {
        showClickedPoint(clickedX, clickedY, cv::Scalar(0, 0, 255));
        paintPlayerMissedClick(clickedX, clickedY);
    } else {
        showClickedPoint(clickedX, clickedY, cv::Scalar(0, 255, 0));
        paintPlayerClickedCar(selectedObjs);
    }

}

void SelectCarsReaction::paintPlayerMissedClick(int x, int y) {
    savePenaltyTime();
    for(KittiObject obj: this->frames.front().getObjectsOfType(Labeltypes::CAR)){
        drawDistToCorrectBox(x, y, obj);
    }
    this->frames.front().colorObjectsOfType(Labeltypes::CAR, cv::Scalar(0, 0, 255));
}

void SelectCarsReaction::paintPlayerClickedCar(std::vector<KittiObject> selectedObjs) {
    saveTime();
    //paint all cars red
    this->frames.front().colorObjectsOfType(Labeltypes::CAR, cv::Scalar(0, 255, 255));

    //paint clicked one green
    KittiObject carToPaint = selectedObjs.back();
    for (KittiObject &item: this->frames.front().getObjects()) {
        if (item == carToPaint) {
            item.setColor(0, 255, 0);
            break;
        }
    }
}
