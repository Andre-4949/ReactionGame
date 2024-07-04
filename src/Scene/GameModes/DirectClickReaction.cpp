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
    KittiObject randomObj = this->frames.front().getObjects()[currentFrame.getRandomlySelectedObject()];
    std::vector<KittiObject> clickedObjs = this->getClickedObjects(x, y);
    if (clickedObjs.empty())return;
    KittiObject clickedObj = clickedObjs.back();
    if (clickedObj == randomObj) {
        waitingOnClick = false;
        clickedObj.getLabel().getBoundingBox().setVisible(false);
        double time_in_nanoseconds = (int) std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();
        double time_in_milliseconds = time_in_nanoseconds * 0.001;
        resultsHandler.addTime(time_in_milliseconds);
    }
}

void DirectClickReaction::update() {
    if (!this->frames.empty()) {
//        this->frames.front().setAllKittiObjectInvisible();
//        this->frames.front().chooseRandomObject();
        this->frames.front().render();
        if (this->getFrames().size() > 0) {
            cv::imshow(Game::session.getWindowName(), this->getFrames().front().getImg());
        }
        cv::waitKey(1);
    }
    showingObjTimePoint = std::chrono::high_resolution_clock::now();
    waitingOnClick = true;

    while (1) {
        double timeSinceImgShown = (int) std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();

        if (timeSinceImgShown >= 3)break;
        if (cv::pollKey() == 27)Game::session.setGameSessionRunning(false);
        if (!this->waitingOnClick)break;
    }

    if (waitingOnClick) {
        // strafzeit
    }
    if (frames.size() > 0)
        this->frames.pop();
    if (frameNames.size() > 0)
        this->frameNames.pop();

}