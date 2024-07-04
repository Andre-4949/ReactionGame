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
        double time_in_milliseconds = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();
        double time_in_seconds = time_in_milliseconds * 0.001;
        resultsHandler.addTime(time_in_seconds);
    }
}

void DirectClickReaction::render() {
    if (this->frames.empty())return;
    this->frames.front().render();
    if (this->getFrames().size() > 0) {
        cv::imshow(Game::session.getWindowName(), this->getFrames().front().getImg());
    }
    cv::waitKey(1);
}

void DirectClickReaction::update() {
    render();
    this->frames.front().chooseRandomObject();
    auto showFrameStart = std::chrono::high_resolution_clock::now();
    while (1) {
        double timeSinceImgShown = (int) std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - showFrameStart).count();

        if (timeSinceImgShown >= 3)break;
        if (cv::pollKey() == 27)Game::session.setGameSessionRunning(false);
    }
    render();
    showingObjTimePoint = std::chrono::high_resolution_clock::now();
    waitingOnClick = true;

    while (1) {
        double timeSinceImgShown = (int) std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();

        if (cv::pollKey() == 27)Game::session.setGameSessionRunning(false);
        if (timeSinceImgShown >= 3)break;
        if (!this->waitingOnClick)break;
    }

    if (waitingOnClick) {
        resultsHandler.addTime(5.0);
    }
    if (frames.size() > 0)
        this->frames.pop();
    if (frameNames.size() > 0)
        this->frameNames.pop();

}