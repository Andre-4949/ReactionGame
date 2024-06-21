//
// Created by andre on 15.06.2024.
//

#include <ctime>
#include <chrono>
#include <opencv2/highgui/highgui.hpp>

#include "../../include/PreGameControlling/GameSession.h"

GameSession::GameSession(Gamemode pMode, Scenery * pScene, std::string pName):mode(pMode), scene(pScene), name(pName)
  {
  }
void test(int a, int b, int c, int d, void* e){
}

void GameSession::loop() {
    int millisecondsPerFrame = (int)(1000.0/60.0);
    auto lastUpdate = std::chrono::high_resolution_clock::now();
    int millisecondCounter = 0,time_in_nanoseconds;
// 
    cv::Mat img = cv::imread("C:\\Users\\linus\\OneDrive\\Desktop\\DHBW\\Module\\2Semester\\BWL\\bildfunktionaleAbteilungsgliederung.png");
    cv::namedWindow("test", 1);
    // cv::setMouseCallback("test", mouseEvents, 0);
    cv::setMouseCallback("test", test, 0);
// 
    while(this->gameSessionRunning){
        time_in_nanoseconds = (int) std::chrono::duration_cast<std::chrono::nanoseconds>(lastUpdate - std::chrono::high_resolution_clock::now()).count();
        millisecondCounter += time_in_nanoseconds*0.000001;
        render();
        if(millisecondCounter>millisecondsPerFrame) {
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

void* GameSession::mouseEvents(int event, int x, int y, int flags, void* userdata) {
    std::cout << x;
    return nullptr;
}

void GameSession::keyEvents() {
//    cv::pollKey();
//    cv::waitKey(10);
}

Scenery *GameSession::getScene()
{
  return scene;
}

