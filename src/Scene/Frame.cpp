//
// Created by andre on 15.06.2024.
//

#include <random>
#include "../../include/Scene/Frame.h"

void Frame::render() {
    for (KittiObject &item: this->objects) {
        item.render(this->img);
    }
}

std::vector<KittiObject> Frame::processClicks(int x, int y) {
    std::vector<KittiObject> clickedObjects;
    for (KittiObject &item: this->objects) {
        if (item.processClicks(x, y))
            clickedObjects.push_back(item);
    }
    return clickedObjects;
}

const std::vector<KittiObject> &Frame::getObjects() const {
    return objects;
}

const KittiObject &Frame::getRandomlySelectedObject() const {
    return randomlySelectedObject;
}

void Frame::chooseRandomObject() {
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, this->objects.size());
    this->randomlySelectedObject = objects[dist(rng)];
}


void Frame::setAllKittiObjectVisible() {
    for (KittiObject &item: this->objects) {
        item.getLabel().getBoundingBox().setVisible(false);
    }
}

void Frame::setAllKittiObjectInvisible() {
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
    for (Label &item: labels){
        if(item.getMFrame() == frameNumber){
            this->objects.emplace_back(item);
        }
    }
    this->img = img;
    chooseRandomObject();
}

void Frame::setImg(const cv::Mat &img) {
    Frame::img = img;
}

const cv::Mat &Frame::getImg() const {
    return img;
}
