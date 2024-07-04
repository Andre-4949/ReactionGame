//
// Created by andre on 15.06.2024.
//

#include "../../include/Scene/Scenery.h"
#include "../../include/PreGameControlling/Game.h"
#include <functional>
#include <stdlib.h>
#include <filesystem>

Scenery::Scenery(int pNumberOfFrames, int pSequence) : numberOfFrames(pNumberOfFrames), sequence(pSequence) {

}

void Scenery::saveTime(){
    double time_in_milliseconds = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();
    double time_in_seconds = time_in_milliseconds * 0.001;
    resultsHandler.addTime(time_in_seconds);
}

void Scenery::savePenaltyTime(){
    resultsHandler.addTime(5.0);
}


void Scenery::mouseEvents(int event, int x, int y, int flags, void *userdata) {

}

void Scenery::keyEvents() {

}

std::vector<KittiObject> Scenery::getClickedObjects(int x, int y) {
    return this->frames.front().processClicks(x, y);
}

void Scenery::render() {
    if (this->frames.empty())return;
    this->frames.front().render();
    if (this->getFrames().size() > 0) {
        cv::imshow(Game::session.getWindowName(), this->getFrames().front().getImg());
    }
    cv::waitKey(1);
}

const ResultsHandler &Scenery::getResultsHandler() const {
    return resultsHandler;
}

std::string
addStringUntilWidthIsReached(std::string originalStr, std::string stringToAppendOrInsert, int maxWidth) {
    while (originalStr.length() < maxWidth) {
        originalStr.insert(0, stringToAppendOrInsert);
    }
    return originalStr;
}

void Scenery::loadFrame(int frameNum, int sequence) {
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string imgPath = folderPath + R"(\data_tracking_image_2\training\image_02\)";
    std::string imgFileName = std::to_string(frameNum);
    std::string sequenceStr = std::to_string(sequence);
    sequenceStr = addStringUntilWidthIsReached(sequenceStr, "0", 4);

    imgFileName = addStringUntilWidthIsReached(imgFileName, "0", 6) + ".png";
    imgPath += sequenceStr + "\\" + imgFileName;
    if (!std::filesystem::exists(imgPath))return;
    frameNames.push(imgPath);
    cv::Mat img = cv::imread(imgPath);
    cv::waitKey(2);
    Frame currentFrame(currentLabels, img, currentFrameNumber);
    frames.push(currentFrame);
}


void Scenery::loadFrames() {
    loadFrame(currentFrameNumber, sequence);
    currentFrameNumber++;
//    for (int i = 0; i < 3; ++i) {
//    }
}


const std::queue<Frame> &Scenery::getFrames() const {
    return frames;
}

const std::queue<std::string> &Scenery::getFrameNames() const {
    return frameNames;
}

void Scenery::loadLabels(int sequence) {
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string labelsPath = folderPath + R"(\data_tracking_label_2\training\label_02\)";
    std::string sequenceStr = std::to_string(sequence);
    std::string labelsFileName = sequenceStr;
    labelsFileName = addStringUntilWidthIsReached(labelsFileName, "0", 4) + ".txt";
    labelsPath += labelsFileName;
    if (!std::filesystem::exists(labelsPath))return;
    currentLabels = Label::loadLabelsFromFile(labelsPath);
}

int Scenery::getSequence() const {
    return sequence;
}

bool Scenery::checkAllFramesShown(){
    if(currentFrameNumber >= numberOfFrames+2){ 
        Game::session.setGameSessionRunning(false);
        return true;
        }
        return false;
}

void Scenery::waitMilliSeconds(int time, std::function<bool(void)> breakCondition){
    auto showFrameStart = std::chrono::high_resolution_clock::now();
        while (1) {
            double timeSinceImgShown = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - showFrameStart).count();

            if (timeSinceImgShown >= time)break;
            if(breakCondition()) break;
            if (cv::pollKey() == 27){
                Game::session.setGameSessionRunning(false);
                break;
                };
        }
}



void Scenery::update(){
    if (checkAllFramesShown()) return;
    setupFrame();
    render();
    this->frames.front().chooseRandomObject();


    makeRandomObjVisible();
    render();
    showingObjTimePoint = std::chrono::high_resolution_clock::now();
    waitingOnClick = true;

    waitMilliSeconds(3000, [this](){return !this->waitingOnClick;});

    if (waitingOnClick) {
        savePenaltyTime();
    }
    
    if (frames.size() > 0)
        this->frames.pop();
    if (frameNames.size() > 0)
        this->frameNames.pop();
}