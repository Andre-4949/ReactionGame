#include <ctime>
#include <chrono>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>

#include "../../include/PreGameControlling/GameSession.h"
#include "../../include/PreGameControlling/Game.h"

GameSession::GameSession(Scenery *pScene, std::string pName) : scene(pScene), name(pName) {
    cv::namedWindow(this->windowName, 1);
}

void mouseCallbackAdapter(int event, int x, int y, int flags, void *userdata) {
    Game::session.mouseEvents(event, x, y, flags, userdata);
}

void GameSession::loop() {
    int millisecondsPerUpdateFrame = (int) (1000.0 / 300.0);
    auto lastUpdate = std::chrono::high_resolution_clock::now();
    int millisecondCounter = 0, frameCounter;
    double time_in_nanoseconds;

    cv::setWindowProperty(this->windowName, cv::WindowPropertyFlags::WND_PROP_FULLSCREEN,
                          cv::WindowPropertyFlags::WND_PROP_FULLSCREEN);
    cv::setMouseCallback(this->windowName, mouseCallbackAdapter, nullptr);
//
//    this->scene->loadFrames();
    scene->loadLabels(scene->getSequence());
    scene->loadFrames();
    while (this->gameSessionRunning) {
        update();
        if (cv::pollKey() == 27)this->gameSessionRunning = false;
    }
}

void GameSession::render() {
    scene->render();
    if (this->scene->getFrames().size() > 0) {
        cv::imshow(this->windowName, this->scene->getFrames().front().getImg());
    }
}

void GameSession::update() {
    scene->loadFrames();
    scene->update();
}

void GameSession::mouseEvents(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        scene->processClicks(x, y);
    }
}

void GameSession::keyEvents() {
//    cv::pollKey();
//    cv::waitKey(10);
}

Scenery *GameSession::getScene() {
    return scene;
}

const std::string &GameSession::getWindowName() const {
    return windowName;
}

void GameSession::setWindowName(const std::string &windowName) {
    GameSession::windowName = windowName;
}

void GameSession::setGameSessionRunning(bool gameSessionRunning) {
    GameSession::gameSessionRunning = gameSessionRunning;
}
