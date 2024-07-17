#include <random>
#include "../../include/Scene/Frame.h"
#include "../../include/PreGameControlling/Game.h"

void Frame::render() {
    for (KittiObject &item: this->objects) {
        item.render();
    }
}

std::vector<KittiObject> &Frame::processClicks(const int x, const int y) {
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

[[maybe_unused]] void Frame::chooseRandomObject() {
    using namespace std;
    random_device device;
    mt19937 rng(device());
    uniform_int_distribution<mt19937::result_type> dist(0, this->objects.size() - 1);
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

Frame::Frame(std::vector<Label>& labels, const cv::Mat& img, const int frameNumber) {

    img.copyTo(origImg);
    for (Label &item: labels) {
        if (item.getMFrame() == frameNumber && Frame::labelFilter.find(item.getMType()) != Frame::labelFilter.end()) {
            KittiObject obj(item);
            this->objects.push_back(obj);
        }
    }
    this->img = img;

}

void Frame::setImg(const cv::Mat &img) {
    Frame::img = img;
}

const cv::Mat &Frame::getImg() const {
    return img;
}

const cv::Mat &Frame::getOriginalImg() const {
    return origImg;
}

void Frame::setColorOfAllObjects(const cv::Scalar& color) {
    for (KittiObject &item: this->objects) {
        item.setColor(color);
    }
}

GTBoundingBox &Frame::getBoundingBoxOfRandomObject() {
    return this->objects[this->indexOfRandomObject].getLabel().getBoundingBox();
}

void Frame::colorObjectsOfType(const std::string& type, const cv::Scalar& color) {
    for (int i = 0; i < this->objects.size(); ++i) {
        if (objects[i].getLabel().getMType() == type) {
            objects[i].setColor(color);
        }
    }
}

std::vector<KittiObject> Frame::getObjectsOfType(const std::string& type) {
    std::vector<KittiObject> objsOfType;

    for (int i = 0; i < this->objects.size(); ++i) {
        if (objects[i].getLabel().getMType() == type) {
            objsOfType.push_back(objects[i]);
        }
    }
    return objsOfType;
}

