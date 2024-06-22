//
// Created by andre on 15.06.2024.
//

#include "../../include/Scene/Scenery.h"
#include <stdlib.h> 

Scenery::Scenery(int pNumberOfFrames, int pSequence):numberOfFrames(pNumberOfFrames), sequence(pSequence)
{

}

void Scenery::mouseEvents(int event, int x, int y, int flags, void *userdata) {

}

void Scenery::keyEvents() {

}

std::vector<KittiObject> Scenery::getClickedObjects(int x, int y) {
    return this->frames.front().processClicks(x, y);
}

void Scenery::render(cv::InputOutputArray &img) {
    this->frames.front().render(img);
}

const ResultsHandler &Scenery::getResultsHandler() const {
    return resultsHandler;
}

void Scenery::loadFrames() {
    // nev-var "KITTI_PATH" ist der Path bis zum Ordner "\KITTI"
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string imgPath = folderPath + R"(\data_tracking_image_2\training\image_02)";
    std::string labelsPath = folderPath + R"(\data_tracking_label_2\training\label_02)";
    if (sequence > 9) {
        imgPath += "00";
        labelsPath += "00";
    } else {
        labelsPath += "000";
        imgPath += "000";
    }

    std::string sequenceStr = std::to_string(sequence);
    imgPath += sequenceStr + "\\";
    labelsPath += sequenceStr + ".txt";
    if (currentFrameNumber <= 1) {
        for (int i = 1; i < 4; i++) {
            imgPath = std::string("00000") + std::to_string(i) + ".png";
            frameNames.push_back(imgPath);
            cv::Mat img = cv::imread(imgPath);
            std::vector<Label> currentLabels = Label::loadLabelsFromFile(labelsPath);
            Frame currentFrame(currentLabels, img, currentFrameNumber);
            frames.push(currentFrame);
        }
        currentFrameNumber = 4;
    } else {
        for (int i = 0; i < 6 - std::to_string(currentFrameNumber).length(); i++) {//fill in remaining empty positions with zeros
            imgPath += "0";
        }
        imgPath += ".png";
        frameNames.push_back(imgPath);
        cv::Mat img = cv::imread(imgPath);
        std::vector<Label> currentLabels = Label::loadLabelsFromFile(labelsPath);
        Frame currentFrame(currentLabels, img, currentFrameNumber);
        frames.push(currentFrame);
        currentFrameNumber++;
    }
}
