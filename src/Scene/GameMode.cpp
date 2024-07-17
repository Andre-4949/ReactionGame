
#include "../../include/Scene/GameMode.h"
#include "../../include/PreGameControlling/Game.h"
#include <functional>
#include <stdlib.h>
#include "cstdlib"
#include "../../include/HelperClasses/Utils.h"
#include <filesystem>

GameMode::GameMode(int pNumberOfFrames, int pSequence) : numberOfFrames(pNumberOfFrames), sequence(pSequence) {
    Util::environmentalVar::checkIfKittiPathIsSet();
}

void GameMode::saveTime(double time) {
    if(time >= 0.0){
        resultsHandler.addTime(time);
        return;
    }
    auto now = std::chrono::high_resolution_clock::now(); 
    double clickTime = Util::timing::getTimeDifference(now, showingObjTimePoint) / Constants::SECONDSTOMILLISECONDS;
    resultsHandler.addTime(clickTime);
}

std::vector<KittiObject> &GameMode::getClickedObjects(int x, int y) {
    return this->frames.front().processClicks(x, y);
}

void GameMode::render() {
    if (this->frames.empty())return;
    this->frames.front().render();
    if (this->getFrames().size() > 0) {
        cv::imshow(Game::session.getWindowName(), Game::session.getCurrentImg());
    }
    cv::waitKey(1);
}

const ResultsHandler &GameMode::getResultsHandler() const {
    return resultsHandler;
}


void GameMode::loadFrame(int frameNum) {
    const std::string imgPath = Util::fileUtil::generateImagePath(frameNum, sequence);
    if (!std::filesystem::exists(imgPath)) {
        std::cout << "Could not find image at: " << imgPath << std::endl;
        return;
    }

    const cv::Mat img = cv::imread(imgPath);
    Frame currentFrame(currentLabels[sequence], img, currentFrameNumber);
    frames.push(currentFrame);
}


void GameMode::loadFrames() {
    if (this->currentLabels.find(this->sequence) == this->currentLabels.end())
        loadLabels();
    loadFrame(currentFrameNumber);
    currentFrameNumber++;
    if (this->frames.empty()) {
        std::cout << "No frames could have been loaded." << std::endl;
    }
}


const std::queue<Frame> &GameMode::getFrames() const {
    return frames;
}

void GameMode::loadLabels() {
    std::string labelsPath = Util::fileUtil::generateLabelFolderPath(sequence);
    if (!std::filesystem::exists(labelsPath))return;
    currentLabels[sequence] = Label::loadLabelsFromFile(labelsPath);
    if (currentLabels.empty()) {
        std::cout << "Program stops as there are no labels to be found. This could cause the programm to end." << std::endl;
        exit(404);
    }
}

bool GameMode::checkAllFramesShown() {
    //+2: +3 due to preloaded frames, -1 due to currentFrameNumber being an index and therefore starting at 0
    if (currentFrameNumber >= numberOfFrames + 2) {
        Game::session.setGameSessionRunning(false);
        return true;
    }
    return false;
}

void GameMode::update() {
    if (checkAllFramesShown() || frames.empty()) return;
    if (this->frames.front().getObjects().empty()){
        std::cout << "frame skipped, because no object was found that matches given labelfilter." << std::endl;
        frames.pop();

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
        std::cout << "Schon eingeschlafen? Zu langsam reagiert! (+5 Sekunden Strafe)" << std::endl;
    }
    this->frames.pop();
}

void GameMode::doWhileWaitingOnInput(){
    //keep empty implementation, as method is not overridden in every child class
}

void GameMode::setupFrame(){
    render();
    this->frames.front().chooseRandomObject();
    makeRandomObjVisible();
    render();
    showingObjTimePoint = std::chrono::high_resolution_clock::now();
    waitingOnInput = true;
}

void GameMode::evaluateInput(std::vector<KittiObject> &objects, int x, int y){
    Frame &currentFrame = frames.front();
    KittiObject &randomObj = currentFrame.getRandomlySelectedObject();
    drawHandler.setImg(currentFrame.getImg());

    bool correctObjClicked = false;
    for(KittiObject obj: objects){
        if(obj == randomObj) correctObjClicked = true;
    }

    //clicked correct object
    if(correctObjClicked){
        saveTime();
        drawHandler.drawPlayerClickedCorrect(x, y, randomObj);
        std::cout << "Richtig! (weitere Reaktionszeit gespeichert)" << std::endl;
    }
    //missed every object or clicked wrong object 
    else{
        saveTime(penaltyTime);
        drawHandler.drawPlayerMissedClick(x, y, randomObj);
        std::cout << "Das war nicht richtig :/ (+5 Sekunden Strafe)" << std::endl;
    }
    render();
    Util::timing::waitMilliSeconds(Constants::SECONDSTOMILLISECONDS * 1);
    objects.clear();
}