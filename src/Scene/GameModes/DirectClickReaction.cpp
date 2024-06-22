#include "../../../include/Scene/GameModes/DirectClickReaction.h"

DirectClickReaction::DirectClickReaction(int pNumberOfFrames, int pSequence) :
        Scenery(pNumberOfFrames, pSequence) {
        
}

DirectClickReaction::~DirectClickReaction() {

}

void DirectClickReaction::processClicks(int x, int y) {
        Frame currentFrame = frames.front();
        KittiObject randomObj = currentFrame.getRandomlySelectedObject();
        KittiObject clickedObj = this->getClickedObjects(x, y).back();
        if(clickedObj == randomObj){
                waitingOnClick = false;
                clickedObj.getLabel().getBoundingBox().setVisible(false);
                double time_in_nanoseconds = (int) std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();
                double time_in_milliseconds = time_in_nanoseconds * 0.001;
                resultsHandler.addTime(time_in_milliseconds);
        }

}

void DirectClickReaction::update(int& frameCounter){
        if(frameCounter % 60 == 0){
                if(!waitingOnClick){
                        Frame currentFrame = frames.front();
                        currentFrame.chooseRandomObject();
                        KittiObject randomObj = currentFrame.getRandomlySelectedObject();
                        randomObj.setColor(255, 0, 0);
                        randomObj.getLabel().getBoundingBox().setVisible(true);
                        showingObjTimePoint = std::chrono::high_resolution_clock::now();
        }
        frameCounter = 0;
}
}