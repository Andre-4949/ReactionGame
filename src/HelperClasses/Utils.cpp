#include "../../include/HelperClasses/Utils.h"
#include "../../include/PreGameControlling/Game.h"
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <opencv2/highgui.hpp>

int Util::fileUtil::getAmountOfFilesInFolder(std::string folderPath) {
    auto dirIter = std::filesystem::directory_iterator(folderPath);
    //iterates over directory with given Path and counts regular files
    int fileCount = std::count_if(
            dirIter,
            {},
            [](auto &entry) { return entry.is_regular_file(); }
    );
    return fileCount;
}

std::string Util::fileUtil::generateImgFolderPathString(int sequenceNr){
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string imgPath = folderPath + R"(\data_tracking_image_2\training\image_02\)";
    std::string sequenceStr = std::to_string(sequenceNr);
    sequenceStr = stringUtil::addStringUntilWidthIsReached(sequenceStr, "0", 4);
    imgPath += sequenceStr;
    return imgPath;
}

std::string Util::fileUtil::generateLabelFolderPath(int sequence) {
    environmentalVar::checkIfKittiPathIsSet();
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string labelsPath = folderPath + R"(\data_tracking_label_2\training\label_02\)";
    std::string sequenceStr = std::to_string(sequence);
    std::string labelsFileName = sequenceStr;
    labelsFileName = stringUtil::addStringUntilWidthIsReached(labelsFileName, "0", 4) + ".txt";
    labelsPath += labelsFileName;
    return labelsPath;
}

std::string Util::fileUtil::generateImagePath(int frameNum, int sequenceNum) {
    std::string imgFileName = std::to_string(frameNum);
    imgFileName = Util::stringUtil::addStringUntilWidthIsReached(imgFileName, "0", 6) + ".png";
    std::string imgFolderPath = Util::fileUtil::generateImgFolderPathString(sequenceNum);
    return imgFolderPath + "\\" + imgFileName;
}

std::string
Util::stringUtil::addStringUntilWidthIsReached(std::string originalStr, std::string stringToAppendOrInsert,
                                               int maxWidth) {
    while (originalStr.length() < maxWidth) {
        originalStr.insert(0, stringToAppendOrInsert);
    }
    return originalStr;
}

void Util::environmentalVar::checkIfKittiPathIsSet() {
    if (std::getenv("KITTI_PATH"))return;
    std::cout << "This programm needs the KITTI images to operate as intended. "
                 "Please download the KITTI image collection and add an environmental variable named "
                 "KITTI_PATH to the folder containing \\data_tracking_image_2 as well as"
                 " \\data_tracking_label_2." << std::endl;
#ifdef _WIN32
    std::cout << "Windows detected" << std::endl;
    std::cout << "Do you want to open the menu to edit environmental variables? [y|n]" << std::endl;
    char answer;
    std::cin >> answer;
    if (answer != 'y')return;
    system("\"C:\\Windows\\system32\\rundll32.exe\" sysdm.cpl,EditEnvironmentVariables");
    std::cout << "Restart your computer once the environmental variables have been set." << std::endl;
    system("pause");
#endif
    exit(0);

}

void Util::timing::waitMilliSeconds(int time, std::function<bool(void)> breakCondition,
                                    std::function<void()> doWhileWaiting) {
    auto showFrameStart = std::chrono::high_resolution_clock::now();
    while (1) {
        doWhileWaiting();
        auto now = std::chrono::high_resolution_clock::now();
        double timeSinceImgShown = getTimeDifference(now, showFrameStart);
        if (timeSinceImgShown >= time)break;
        if (breakCondition()) break;
        if (cv::pollKey() == 27) {
            Game::session.setGameSessionRunning(false);
            break;
        };
    }


}

double Util::timing::getTimeDifference(std::chrono::_V2::system_clock::time_point later,
                                       std::chrono::_V2::system_clock::time_point earlier) {
    using namespace std::chrono;
    double timeDifference = duration_cast<milliseconds>(later - earlier).count();
    return timeDifference;
}
