#include <ctime>
#include <chrono>
#include <opencv2/highgui/highgui.hpp>
#include <utility>
#include <opencv2/highgui/highgui_c.h>

#include "../../include/PreGameControlling/GameSession.h"
#include "../../include/PreGameControlling/Game.h"
#include "../../include/Scene/GameModes/DirectClickReaction.h"

GameSession::GameSession(Scenery *pScene, std::string pName) : scene(pScene), name(std::move(pName)) {
    cv::namedWindow(this->windowName, 1);
}

//gets called every mouse click, move or scroll --> extract leftclicks
void mouseCallbackAdapter(int event, int x, int y, int flags, void *userdata) {
    Game::session.mouseEvents(event, x, y, flags, userdata);
}

void GameSession::loop() {
    //Game Window setup
    cv::setWindowProperty(this->windowName, cv::WindowPropertyFlags::WND_PROP_FULLSCREEN,
                          cv::WindowPropertyFlags::WND_PROP_FULLSCREEN);
    cv::setMouseCallback(this->windowName, mouseCallbackAdapter, nullptr);
    scene->loadFrames();
    //main game-loop
    while (this->gameSessionRunning) {
        update();
        if (cv::pollKey() == 27)this->gameSessionRunning = false;
    }
}

//render call gets passed through all the way to each bounding-box
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

Scenery *GameSession::getScene() {
    return scene;
}

const std::string &GameSession::getWindowName() const {
    return windowName;
}

const cv::Mat& GameSession::getCurrentImg() const{
    return scene->getFrames().front().getImg();
}

void GameSession::setGameSessionRunning(bool gameSessionRunning) {
    GameSession::gameSessionRunning = gameSessionRunning;
}
