#include "../../include/HelperClasses/Utils.h"
#include "../../include/PreGameControlling/Game.h"
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <opencv2/highgui.hpp>

int Util::fileUtil::getAmountOfFilesInFolder(const std::string& folderPath) {
    auto dirIter = std::filesystem::directory_iterator(folderPath);
    //iterates over directory with given Path and counts regular files
    const int fileCount = std::count_if(
            dirIter,
            {},
            [](auto &entry) { return entry.is_regular_file(); }
    );
    return fileCount;
}

std::string Util::fileUtil::generateImgFolderPathString(const int sequenceNr){
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string imgPath = folderPath + R"(\data_tracking_image_2\training\image_02\)";
    std::string sequenceStr = std::to_string(sequenceNr);
    sequenceStr = stringUtil::addStringUntilWidthIsReached(sequenceStr, "0", 4);
    imgPath += sequenceStr;
    return imgPath;
}

std::string Util::fileUtil::generateLabelFolderPath(const int sequence) {
    environmentalVar::checkIfKittiPathIsSet();
    std::string folderPath = std::getenv("KITTI_PATH");
    std::string labelsPath = folderPath + R"(\data_tracking_label_2\training\label_02\)";
    std::string sequenceStr = std::to_string(sequence);
    std::string labelsFileName = sequenceStr;
    labelsFileName = stringUtil::addStringUntilWidthIsReached(labelsFileName, "0", 4) + ".txt";
    labelsPath += labelsFileName;
    return labelsPath;
}

std::string Util::fileUtil::generateImagePath(const int frameNum, const int sequenceNum) {
    std::string imgFileName = std::to_string(frameNum);
    imgFileName = Util::stringUtil::addStringUntilWidthIsReached(imgFileName, "0", 6) + ".png";
    const std::string imgFolderPath = Util::fileUtil::generateImgFolderPathString(sequenceNum);
    return imgFolderPath + "\\" + imgFileName;
}

std::string
Util::stringUtil::addStringUntilWidthIsReached(std::string originalStr, const std::string& stringToAppendOrInsert,
                                               const int maxWidth) {
    while (originalStr.length() < maxWidth) {
        originalStr.insert(0, stringToAppendOrInsert);
    }
    return originalStr;
}

void Util::environmentalVar::checkIfKittiPathIsSet() {
    if (std::getenv("KITTI_PATH"))return;
    std::cout << "This programm needs the KITTI images to operate as intended. "
                 "Please download the KITTI image collection including the corresponding labels to a common folder. "
                 "Add an environmental variable named KITTI_PATH which points to the folder "
                 "containing \\data_tracking_image_2 as well as \\data_tracking_label_2.\n\t"
                 "Note: The downloaded zip-files need to be extracted yet the parent folders should not double." << std::endl;
    std::cout << "Link to KITTI images:\n\n\thttps://s3.eu-central-1.amazonaws.com/avg-kitti/data_tracking_image_2.zip (14.7 GB)"
                 "\n\nLink to KITTI labels:\n\n\thttps://s3.eu-central-1.amazonaws.com/avg-kitti/data_tracking_label_2.zip (2.2 MB)" << std::endl;
#ifdef _WIN32
    std::cout << "Windows detected" << std::endl;
    std::cout << "Do you want to open the menu to edit environmental variables? [y|n]" << std::endl;
    char answer;
    std::cin >> answer;
    if (answer != 'y')exit(0);
    system(R"("C:\Windows\system32\rundll32.exe" sysdm.cpl,EditEnvironmentVariables)");
    std::cout << "Restart your computer once the environmental variables have been set." << std::endl;
    system("pause");
#endif
    exit(0);

}

void Util::timing::waitMilliSeconds(const int time, const std::function<bool(void)>& breakCondition,
                                    const std::function<void()>& doWhileWaiting) {
    const auto showFrameStart = std::chrono::high_resolution_clock::now();
    while (1) {
        doWhileWaiting();
        const auto now = std::chrono::high_resolution_clock::now();
        const double timeSinceImgShown = getTimeDifference(now, showFrameStart);
        if (timeSinceImgShown >= time)break;
        if (breakCondition()) break;
        if (cv::pollKey() == 27) {
            Game::session.setGameSessionRunning(false);
            break;
        };
    }
}

const double Util::timing::getTimeDifference(const std::chrono::_V2::system_clock::time_point later,
                                       const std::chrono::_V2::system_clock::time_point earlier) {
    using namespace std::chrono;
    const double timeDifference = duration_cast<milliseconds>(later - earlier).count();
    return timeDifference;
}
