#include "../../../include/Scene/GameModes/DirectClickReaction.h"
#include "../../../include/PreGameControlling/Game.h"

DirectClickReaction::DirectClickReaction(int pNumberOfFrames, int pSequence) :
        Scenery(pNumberOfFrames, pSequence) {

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
    if (clickedObjs.empty()){
            savePenaltyTime();
            return;
        }
    KittiObject clickedObj = clickedObjs.back();
    if (clickedObj == randomObj) {
        saveTime();
    }
}


// void DirectClickReaction::update() {
//     if(currentFrameNumber >= numberOfFrames+2){ 
//         Game::session.setGameSessionRunning(false);
//         return;
//         }
//     render();
//     this->frames.front().chooseRandomObject();
//     //KittiObject randomObj = 
//     // this->frames.front().getObjects()[this->frames.front().getRandomlySelectedObject()].getLabel().getBoundingBox().setVisible(true);
//     //randomObj;

//     auto showFrameStart = std::chrono::high_resolution_clock::now();
//     while (1) {
//         double timeSinceImgShown = (int) std::chrono::duration_cast<std::chrono::seconds>(
//                 std::chrono::high_resolution_clock::now() - showFrameStart).count();

//         if (timeSinceImgShown >= 3)break;
//         if (cv::pollKey() == 27)Game::session.setGameSessionRunning(false);
//     }
//     render();
//     showingObjTimePoint = std::chrono::high_resolution_clock::now();
//     waitingOnClick = true;

//     while (1) {
//         double timeSinceImgShown = (int) std::chrono::duration_cast<std::chrono::seconds>(
//                 std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();

//         if (cv::pollKey() == 27)Game::session.setGameSessionRunning(false);
//         if (timeSinceImgShown >= 3)break;
//         if (!this->waitingOnClick)break;
//     }

//     if (waitingOnClick) {
//         savePenaltyTime();
//     }

//     if (frames.size() > 0)
//         this->frames.pop();
//     if (frameNames.size() > 0)
//         this->frameNames.pop();

// }

void DirectClickReaction::makeRandomObjVisible(){
    Scenery::waitMilliSeconds(2000);
    frames.front().getBoundingBoxOfRandomObject().setVisible(true);
}

void DirectClickReaction::setupFrame(){
    
}