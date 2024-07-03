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
    this->frames.front().render();
}

const ResultsHandler &Scenery::getResultsHandler() const {
    return resultsHandler;
}

std::string
addStringUntilWidthIsReached(std::string originalStr, std::string stringToAppendOrInsert, int maxWidth, bool front) {
    while (originalStr.length() < maxWidth) {
        if (front) {
            originalStr.insert(0, stringToAppendOrInsert);
        } else {
            originalStr.append(stringToAppendOrInsert);
        }
    }
    return originalStr;
}

void Scenery::loadFrame(int frameNum, int sequence) {
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string imgPath = folderPath + R"(\data_tracking_image_2\training\image_02)";
    std::string imgFileName = std::to_string(frameNum);
    std::string labelsPath = folderPath + R"(\data_tracking_label_2\training\label_02)";
    std::string labelsFileName = std::to_string(sequence);

    labelsFileName = addStringUntilWidthIsReached(labelsFileName, "0", 4, true) + ".txt";
    labelsPath += labelsFileName;

    imgFileName = addStringUntilWidthIsReached(imgFileName, "0", 6, true) + ".png";
    imgPath += imgFileName;
    if (!(std::filesystem::exists(imgPath) && std::filesystem::exists(labelsPath)))return;
    frameNames.push_back(imgPath);
    cv::Mat img = cv::imread(imgPath);
    std::vector<Label> currentLabels = Label::loadLabelsFromFile(labelsPath);
    Frame currentFrame(currentLabels, img, currentFrameNumber);
    frames.push(currentFrame);
}


void Scenery::loadFrames() {
    // nev-var "KITTI_PATH" ist der Path bis zum Ordner "\KITTI"
//    std::string folderPath = std::getenv("KITTI_PATH");
//    std::string imgPath = folderPath + R"(\data_tracking_image_2\training\image_02)";
//    std::string labelsPath = folderPath + R"(\data_tracking_label_2\training\label_02)";
//    imgPath = addStringUntilWidthIsReached(imgPath, "0", 4, false);
//    labelsPath = addStringUntilWidthIsReached(imgPath, "0", 4, false);
//    if (sequence > 9) {
//        imgPath += "00";
//        labelsPath += "00";
//    } else {
//        labelsPath += "000";
//        imgPath += "000";
//    }

//    std::string sequenceStr = std::to_string(sequence);
//    imgPath += sequenceStr + "\\";
//    labelsPath += sequenceStr + ".txt";

    for (int i = 0; i < 3; ++i) {
        loadFrame(currentFrameNumber, sequence);
        currentFrameNumber++;
    }
}


const std::queue<Frame> &Scenery::getFrames() const {
    return frames;
}
