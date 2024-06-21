//
// Created by andre on 15.06.2024.
//

#include <ctime>
#include <chrono>
#include <opencv2/highgui/highgui.hpp>

#include "../../include/PreGameControlling/GameSession.h"

GameSession::GameSession(Gamemode pMode, Scenery *pScene, std::string pName) : mode(pMode), scene(pScene), name(pName) {
}

void test(int a, int b, int c, int d, void *e) {
    GameSession::mouseEvents(a, b, c, d, e);
}

void GameSession::loop() {
    int millisecondsPerFrame = (int) (1000.0 / 60.0);
    auto lastUpdate = std::chrono::high_resolution_clock::now();
    int millisecondCounter = 0;
    double time_in_nanoseconds;
    std::string path;
    std::cout << "Bitte gib einen Pfad zu einem Bild an:\n\t";
    std::cin >> path;
    cv::Mat img = cv::imread(path);
    cv::namedWindow("test", 1);

    cv::setMouseCallback("test", test, 0);
//
    cv::imshow("test", img);
    while (this->gameSessionRunning) {
        time_in_nanoseconds = (int) std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - lastUpdate).count();
        millisecondCounter += static_cast<int>(time_in_nanoseconds) * 0.000001;
        render();
        if (millisecondCounter > millisecondsPerFrame) {
            update();
            lastUpdate = std::chrono::high_resolution_clock::now();
            millisecondCounter %= 1000;
        }
        if (cv::pollKey() == 27)this->gameSessionRunning = false;
    }
}

void GameSession::render() {

}

void GameSession::update() {

}

void *GameSession::mouseEvents(int event, int x, int y, int flags, void *userdata) {

    return nullptr;
}

void GameSession::keyEvents() {
//    cv::pollKey();
//    cv::waitKey(10);
}

Scenery *GameSession::getScene() {
    return scene;
}

