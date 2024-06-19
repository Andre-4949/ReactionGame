//
// Created by andre on 15.06.2024.
//

#include <ctime>
#include <chrono>
#include <opencv2/highgui/highgui.hpp>

#include "../../include/PreGameControlling/GameSession.h"

void GameSession::loop() {
    int millisecondsPerFrame = (int)(1000.0/60.0);
    auto lastUpdate = std::chrono::high_resolution_clock::now();
    int millisecondCounter = 0,time_in_nanoseconds;
    while(this->gameSessionRunning){
        time_in_nanoseconds = (int) std::chrono::duration_cast<std::chrono::nanoseconds>(lastUpdate - std::chrono::high_resolution_clock::now()).count();
        millisecondCounter += time_in_nanoseconds*0.000001;
        if(millisecondCounter>millisecondsPerFrame) {
            render();
            update();
            lastUpdate = std::chrono::high_resolution_clock::now();
            millisecondCounter %=1000;
        }
    }
}

void GameSession::render() {

}

void GameSession::update() {

}

void GameSession::mouseEvents(int event, int x, int y, int flags, void* userdata) {

}

void GameSession::keyEvents() {
//    cv::pollKey();
//    cv::waitKey(10);
}

