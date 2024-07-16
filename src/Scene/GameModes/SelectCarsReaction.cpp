
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
    waitingOnInput = false;
    std::vector<KittiObject> &selectedObjs = this->getClickedObjects(x, y);
    evaluateInput(selectedObjs, x, y);
    ++this->sequence %= 20;
}

void SelectCarsReaction::makeRandomObjVisible() {
    // keep empty implementation to not call inherited
}


void SelectCarsReaction::evaluateInput(std::vector<KittiObject> &objects, int x, int y) {
    Frame &currentFrame = frames.front();
    drawHandler.setImg(currentFrame.getImg());
    bool correctObjClicked = false;
    for(KittiObject obj: objects){
        if(obj.getLabel().getMType() == Labeltypes::CAR) correctObjClicked = true;
    }
    
    //clicked correct object
    if(correctObjClicked){
        saveTime();
        drawPlayerClickedCorrect(x, y);
        std::cout << "Richtig! (weitere Reaktionszeit gespeichert)" << std::endl;
    }
    // missed every object or clicked object isn't a car
    else{
        saveTime(penaltyTime);
        drawPlayerMissedClick(x, y);
        std::cout << "Das war nicht richtig :/ (+5 Sekunden Strafe)" << std::endl;
    } 
    render();
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
    objects.clear();
}

void SelectCarsReaction::drawPlayerMissedClick(int x, int y) {
    Frame &currentFrame = this->frames.front();
    drawHandler.drawClickedPoint(x, y, Constants::RED);

    //draw distance to every box that would've been correct and make them red
    for(KittiObject obj: currentFrame.getObjectsOfType(Labeltypes::CAR)){
        GTBoundingBox box = obj.getLabel().getBoundingBox();
        drawHandler.drawDistToCorrectBox(x, y, box);
    }
    currentFrame.colorObjectsOfType(Labeltypes::CAR, Constants::RED);
}

void SelectCarsReaction::drawPlayerClickedCorrect(int x, int y) {
    Frame &currentFrame = this->frames.front();
    drawHandler.drawClickedPoint(x, y, Constants::GREEN);

    //color all cars yellow
    currentFrame.colorObjectsOfType(Labeltypes::CAR, Constants::YELLOW);
    std::vector<KittiObject> &selectedObjs = this->getClickedObjects(x, y);

    //color clicked car green
    KittiObject carToPaint = selectedObjs.back();
    for (KittiObject &item: currentFrame.getObjects()) {
        if (item == carToPaint) {
            item.setColor(Constants::GREEN);
            break;
        }
    }
}
