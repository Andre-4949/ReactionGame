#include <iostream>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "../include/Scene/HelperClasses/Label.h"
#include "../include/PreGameControlling/Game.h"

#define peace return
#define out 0

int main(const int argc, const char* argv[]) {
    Game(argc, argv).start();
    peace out;
}