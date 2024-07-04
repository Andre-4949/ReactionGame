//
// Created by andre on 15.06.2024.
//

#include "../../include/Scene/Scenery.h"
#include <stdlib.h>
#include <filesystem>

Scenery::Scenery(int pNumberOfFrames, int pSequence) : numberOfFrames(pNumberOfFrames), sequence(pSequence) {

}

void Scenery::mouseEvents(int event, int x, int y, int flags, void *userdata) {

}

void Scenery::keyEvents() {

}

std::vector<KittiObject> Scenery::getClickedObjects(int x, int y) {
    return this->frames.front().processClicks(x, y);
}

void Scenery::render() {
    if (!frames.empty())
        this->frames.front().render();
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
