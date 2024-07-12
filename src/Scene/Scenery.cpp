
#include "../../include/Scene/Scenery.h"
#include "../../include/PreGameControlling/Game.h"
#include <functional>
#include <stdlib.h>
#include "cstdlib"
#include "../../include/HelperClasses/Utils.h"
#include <filesystem>

Scenery::Scenery(int pNumberOfFrames, int pSequence) : numberOfFrames(pNumberOfFrames), sequence(pSequence) {
    Util::environmentalVar::checkIfKittiPathIsSet();
}

void Scenery::saveTime() {
    auto now = std::chrono::high_resolution_clock::now(); 
    double clickTime = Util::timing::getTimeDifference(now, showingObjTimePoint) / Constants::SECONDSTOMILLISECONDS;
    resultsHandler.addTime(clickTime);
}

void Scenery::savePenaltyTime() {
    resultsHandler.addTime(penaltyTime);
}


// void Scenery::mouseEvents(int event, int x, int y, int flags, void *userdata) {

// }

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

void Scenery::loadFrame(int frameNum) {
    std::string imgPath = Util::fileUtil::generateImagePath(frameNum, sequence);
    if (!std::filesystem::exists(imgPath)) {
        std::cout << "Could not find image at: " << imgPath << std::endl;
        return;
    }
    frameNames.push(imgPath);
    cv::Mat img = cv::imread(imgPath);
    Frame currentFrame(currentLabels[sequence], img, currentFrameNumber);
    frames.push(currentFrame);
}


void Scenery::loadFrames() {
    if (this->currentLabels.find(this->sequence) == this->currentLabels.end())
        loadLabels();
    loadFrame(currentFrameNumber);
    currentFrameNumber++;
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

void Scenery::loadLabels() {
    std::string labelsPath = Util::fileUtil::generateLabelFolderPath(sequence);
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
    //+3 due to preloaded frames
    if (currentFrameNumber >= numberOfFrames + 3) {
        Game::session.setGameSessionRunning(false);
        return true;
    }
    return false;
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
    if (checkAllFramesShown() || frames.empty()) return;
    if (this->frames.front().getObjects().empty()){
        std::cout << "frame skipped, because no object was found that matches given labelfilter." << std::endl;
        frames.pop();
        frameNames.pop();
        return;
    }
    setupFrame();
    Util::timing::waitMilliSeconds(defaultTimeToWaitForOneFrame,
        [this]() { return !this->waitingOnInput; },
        [this]() { this->doWhileWaitingOnInput();}
    );
    if (waitingOnInput) {
        savePenaltyTime();
    }
    this->frames.pop();
    this->frameNames.pop();
}

void Scenery::doWhileWaitingOnInput(){
    //keep empty, as method is not overridden in every child class
}

void Scenery::setupFrame(){
    render();
    this->frames.front().chooseRandomObject();
    makeRandomObjVisible();
    render();
    showingObjTimePoint = std::chrono::high_resolution_clock::now();
    waitingOnInput = true;
}

void Scenery::evaluateInput(std::vector<KittiObject> &objects, int x, int y){
    Frame currentFrame = frames.front();
    KittiObject randomObj = currentFrame.getRandomlySelectedObject();
    
     //missed every object
    if (objects.empty()) {
        onPlayerMissedClick(x, y);
        return;
    }
    KittiObject clickedObj = objects.back();
    //clicked correct object
    if (clickedObj == randomObj) {
        onPlayerClickedCorrect(x, y);
    }
    //clicked wrong object
    else{
        onPlayerMissedClick(x, y);
    }
    objects.clear();
}
