#include "../../include/Scene/Scenery.h"
#include "../../include/PreGameControlling/Game.h"
#include <functional>
#include <stdlib.h>
#include "cstdlib"
#include <filesystem>

void kittiPathNotSet();

Scenery::Scenery(int pNumberOfFrames, int pSequence) : numberOfFrames(pNumberOfFrames), sequence(pSequence) {
    if (std::getenv("KITTI_PATH"))return;
    kittiPathNotSet();
}

void Scenery::saveTime() {
    double time_in_milliseconds = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - showingObjTimePoint).count();
    double time_in_seconds = time_in_milliseconds * 0.001;
    resultsHandler.addTime(time_in_seconds);
}

void Scenery::savePenaltyTime() {
    resultsHandler.addTime(5.0);
}


void Scenery::mouseEvents(int event, int x, int y, int flags, void *userdata) {

}

void Scenery::keyEvents() {

}

std::vector<KittiObject> &Scenery::getClickedObjects(int x, int y) {
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
    if (!std::filesystem::exists(imgPath)) {
        std::cout << "Could not find image at: " << imgPath << std::endl;
        return;
    }
    frameNames.push(imgPath);
    cv::Mat img = cv::imread(imgPath);
    cv::waitKey(2);
    Frame currentFrame(currentLabels[sequence], img, currentFrameNumber);
    frames.push(currentFrame);
}


void Scenery::loadFrames() {
    if (this->currentLabels.find(this->sequence) == this->currentLabels.end())
        loadLabels(sequence);
    loadFrame(currentFrameNumber++, sequence);
    if (this->frames.empty()) {
        std::cout << "No frames could have been loaded." << std::endl;
    }
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
    currentLabels[sequence] = Label::loadLabelsFromFile(labelsPath);
    if (currentLabels.empty()) {
        std::cout << "Program stops as there are no labels to be found. This could cause the programm to end." << std::endl;
        exit(404);
    }
}

int Scenery::getSequence() const {
    return sequence;
}

bool Scenery::checkAllFramesShown() {
    if (currentFrameNumber >= numberOfFrames + 3) {//+3 due to preloaded frames
        Game::session.setGameSessionRunning(false);
        return true;
    }
    return false;
}

void Scenery::waitMilliSeconds(int time, std::function<bool(void)> breakCondition, std::function<void()> doWhileWaiting) {
    auto showFrameStart = std::chrono::high_resolution_clock::now();
    while (1) {
        doWhileWaiting();
        double timeSinceImgShown = (int) std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - showFrameStart).count();

        if (timeSinceImgShown >= time)break;
        if (breakCondition()) break;
        if (cv::pollKey() == 27) {
            Game::session.setGameSessionRunning(false);
            break;
        };
    }
}

void Scenery::showClickedPoint(int x, int y, cv::Scalar color) {
    cv::Mat img = getFrames().front().getImg();
    helper::Point clickedPoint = helper::Point(x, y);
    cv::circle(img, clickedPoint.toCvPoint(), 3, color, -1);
}

helper::Point getVerticalIntersectionPoint(double slope, double yIntercept, int boxX) {
    int intersectionX = boxX;
    int intersectionY = -(slope * boxX + yIntercept);
    return helper::Point(intersectionX, intersectionY);
}

helper::Point getHorizontalIntersectionPoint(double slope, double yIntercept, int boxY) {
    int intersectionY = -boxY;
    int intersectionX = (1 / slope) * (boxY - yIntercept);
    return helper::Point(intersectionX, intersectionY);
}


void Scenery::drawDistToCorrectBox(int x, int y, KittiObject correctObj) {
    y *= -1;
    cv::Mat img = getFrames().front().getImg();
    helper::Point interSectionPoint;
    GTBoundingBox correctBox = correctObj.getLabel().getBoundingBox();
    int boxCenterX = correctBox.getCenter().getX();
    int boxCenterY = -(correctBox.getCenter().getY());
    int distX = boxCenterX - x;
    int distY = boxCenterY - y;
    double slope = ((distY) / (double) distX);
    double yIntercept = y - (slope * x);
    int distBorderX = std::min(abs(x - correctBox.getTopLeft().getX()), abs(x - correctBox.getBottomRight().getX()));
    int distBorderY = std::min(abs(y+correctBox.getTopLeft().getY()), abs(y+correctBox.getBottomRight().getY()));
    if(x <= correctBox.getBottomRight().getX() && x >= correctBox.getTopLeft().getX()) distBorderX = 0;
    if(y >= -correctBox.getBottomRight().getY() && y <= -correctBox.getTopLeft().getY()) distBorderY = 0;

    if (distBorderX > distBorderY) {
        if (distX > 0) {
            interSectionPoint = getVerticalIntersectionPoint(slope, yIntercept, correctBox.getTopLeft().getX());
        } else {
            interSectionPoint = getVerticalIntersectionPoint(slope, yIntercept, correctBox.getBottomRight().getX());
        }
    } else {
        if (distY < 0) {
            interSectionPoint = getHorizontalIntersectionPoint(slope, yIntercept, -correctBox.getTopLeft().getY());
        } else {
            interSectionPoint = getHorizontalIntersectionPoint(slope, yIntercept, -correctBox.getBottomRight().getY());
        }
    }
    cv::line(img, helper::Point(x, -y).toCvPoint(), interSectionPoint.toCvPoint(), cv::Scalar(0, 0, 255), 2);
}

void Scenery::update() {
    if (checkAllFramesShown()) return;
    setupFrame();
    render();
    if (frames.empty())return;
    this->frames.front().chooseRandomObject();


    makeRandomObjVisible();
    render();
    showingObjTimePoint = std::chrono::high_resolution_clock::now();
    waitingOnClick = true;

    if (defaultTimeToWaitForOneFrame > 0) {
        waitMilliSeconds(defaultTimeToWaitForOneFrame, [this]() { return !this->waitingOnClick; }, [this](){this->doWhileWaitingOnClick();});
    }
    if (waitingOnClick) {
        savePenaltyTime();
    }

    if (frames.size() > 0)
        this->frames.pop();
    if (frameNames.size() > 0)
        this->frameNames.pop();
}

void kittiPathNotSet() {
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


void Scenery::doWhileWaitingOnClick(){
    //keep empty, as mehtod is not overidden in every child class
}