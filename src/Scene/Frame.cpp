#include <random>
#include "../../include/Scene/Frame.h"

void Frame::render() {
    for (KittiObject &item: this->objects) {
        item.render();
    }
}

std::vector<KittiObject> &Frame::processClicks(int x, int y) {
    std::vector<KittiObject> *clickedObjects = new std::vector<KittiObject>();
    for (KittiObject &item: this->objects) {
        if (item.processClicks(x, y))
            clickedObjects->push_back(item);
    }
    return *clickedObjects;
}

std::vector<KittiObject> &Frame::getObjects() {
    return objects;
}

KittiObject& Frame::getRandomlySelectedObject() {
    return this->objects[indexOfRandomObject];
}

void Frame::chooseRandomObject() {
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, this->objects.size() - 1);
    indexOfRandomObject = dist(rng);
    objects[indexOfRandomObject].getLabel().getBoundingBox().setVisible(true);
}

void Frame::setAllKittiObjectsInvisible() {
    for (KittiObject &item: this->objects) {
        item.getLabel().getBoundingBox().setVisible(false);
    }
}

void Frame::setAllKittiObjectsVisible() {
    for (KittiObject &item: this->objects) {
        item.getLabel().getBoundingBox().setVisible(true);
    }
}

Frame::Frame() {

}

void Frame::setObjects(const std::vector<KittiObject> &objects) {
    Frame::objects = objects;
}

Frame::Frame(std::vector<Label> labels, cv::Mat img, int frameNumber) {
    img.copyTo(origImg);
    for (Label &item: labels) {
        if (item.getMFrame() == frameNumber && Frame::labelFilter.find(item.getMType()) != Frame::labelFilter.end()) {
            this->objects.emplace_back(item);
        }
    }
    this->img = img;
//    chooseRandomObject();
}

void Frame::setImg(const cv::Mat &img) {
    Frame::img = img;
}

const cv::Mat &Frame::getImg() const {
    return img;
}

const cv::Mat &Frame::getOrigImg() const {
    return origImg;
}

void Frame::setColorOfAllObjects(cv::Scalar color) {
    for (KittiObject &item: this->objects) {
        item.setColor(color);
    }
}

GTBoundingBox &Frame::getBoundingBoxOfRandomObject() {
    return this->objects[this->indexOfRandomObject].getLabel().getBoundingBox();
}

const std::unordered_set<std::string> &Frame::getLabelFilter() const {
    return labelFilter;
}

void Frame::setLabelFilter(const std::unordered_set<std::string> &labelFilter) {
    Frame::labelFilter = labelFilter;
}

void Frame::colorObjectsOfType(std::string type, cv::Scalar color) {
    for (int i = 0; i < this->objects.size(); ++i) {
        if (objects[i].getLabel().getMType() == type) {
            objects[i].setColor(color);
        }
    }
}

std::vector<KittiObject> Frame::getObjectsOfType(std::string type) {
    std::vector<KittiObject> objsOfType;

    for (int i = 0; i < this->objects.size(); ++i) {
        if (objects[i].getLabel().getMType() == type) {
            objsOfType.push_back(objects[i]);
        }
    }

    return objsOfType;
}

