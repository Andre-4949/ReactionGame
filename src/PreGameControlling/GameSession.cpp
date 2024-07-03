//
// Created by andre on 15.06.2024.
//

#include <ctime>
#include <chrono>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>

#include "../../include/PreGameControlling/GameSession.h"
#include "../../include/PreGameControlling/Game.h"

GameSession::GameSession(Gamemode pMode, Scenery *pScene, std::string pName) : mode(pMode), scene(pScene), name(pName) {
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
    while (this->gameSessionRunning) {
//        time_in_nanoseconds = (int) std::chrono::duration_cast<std::chrono::nanoseconds>(
//                std::chrono::high_resolution_clock::now() - lastUpdate).count();
//        millisecondCounter += static_cast<int>(time_in_nanoseconds) * 0.000001;

//        if (millisecondCounter > millisecondsPerUpdateFrame) {
//            update(frameCounter);
//            lastUpdate = std::chrono::high_resolution_clock::now();
//            millisecondCounter %= 1000;
//            frameCounter++;
//        }
        render();
        if (cv::pollKey() == 27)this->gameSessionRunning = false;
    }
}

void GameSession::render() {
    if(this->currentImage.empty())
        scene->render();
    cv::imshow(this->windowName,this->scene->getFrames().front().getImg());
}

void GameSession::update() {
    scene->loadFrames();
    scene->update(frameCounter);
}

void *GameSession::mouseEvents(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        std::cout << "x: " << x << " | y: " << y << std::endl;
        scene->processClicks(x, y);
    }
    return nullptr;
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

const cv::Mat &GameSession::getCurrentImage() const {
    return currentImage;
}

void GameSession::setCurrentImage(const cv::Mat &currentImage) {
    GameSession::currentImage = currentImage;
}
