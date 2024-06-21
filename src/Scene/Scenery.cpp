//
// Created by andre on 15.06.2024.
//

#include "../../include/Scene/Scenery.h"

Scenery::Scenery(int pNumberOfFrames):numberOfFrames(pNumberOfFrames)
{

}

void Scenery::mouseEvents(int event, int x, int y, int flags, void *userdata) {

}

void Scenery::keyEvents() {

}

std::vector<KittiObject> Scenery::getClickedObjects(int x, int y) {
    return this->frames.front().processClicks(x,y);
}

void Scenery::render(cv::InputOutputArray &img) {
    this->frames.front().render(img);
}

const ResultsHandler &Scenery::getResultsHandler() const {
    return resultsHandler;
}
