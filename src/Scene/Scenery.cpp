
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

void Scenery::saveTime(double time) {
    if(time >= 0.0){
        resultsHandler.addTime(time);
        return;
    }
    auto now = std::chrono::high_resolution_clock::now(); 
    double clickTime = Util::timing::getTimeDifference(now, showingObjTimePoint) / Constants::SECONDSTOMILLISECONDS;
    resultsHandler.addTime(clickTime);
}

std::vector<KittiObject> &Scenery::getClickedObjects(int x, int y) {
    return this->frames.front().processClicks(x, y);
}

void Scenery::render() {
    if (this->frames.empty())return;
    this->frames.front().render();
    if (this->getFrames().size() > 0) {
        cv::imshow(Game::session.getWindowName(), Game::session.getCurrentImg());
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
    //+2: +3 due to preloaded frames, -1 due to currentFrameNumber being an index and therefore starting at 0
    if (currentFrameNumber >= numberOfFrames + 2) {
        Game::session.setGameSessionRunning(false);
        return true;
    }
    return false;
}

void Scenery::update() {
    if (checkAllFramesShown() || frames.empty()) return;
    if (this->frames.front().getObjects().empty()){
        std::cout << "frame skipped, because no object was found that matches given labelfilter." << std::endl;
        frames.pop();
        frameNames.pop();

        //increase numberOfFrames to account for skipped frame
        numberOfFrames++;
        return;
    }
    setupFrame();
    Util::timing::waitMilliSeconds(defaultTimeToWaitForOneFrame,
        [this]() { return !this->waitingOnInput; },
        [this]() { this->doWhileWaitingOnInput();}
    );
    if (waitingOnInput) {
        saveTime(penaltyTime);
    }
    this->frames.pop();
    this->frameNames.pop();
}

void Scenery::doWhileWaitingOnInput(){
    //keep empty implementation, as method is not overridden in every child class
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
    Frame &currentFrame = frames.front();
    KittiObject &randomObj = currentFrame.getRandomlySelectedObject();
    drawHandler.setImg(currentFrame.getImg());

    //missed every object or clicked wrong object 
    if (objects.empty() || objects.back() != randomObj) {
        saveTime(penaltyTime);
        drawHandler.drawPlayerMissedClick(x, y, randomObj);
    }
    //clicked correct object
    else{
        saveTime();
        drawHandler.drawPlayerClickedCorrect(x, y, randomObj);
    }
    render();
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
    objects.clear();
}