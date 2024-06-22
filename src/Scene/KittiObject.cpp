//
// Created by andre on 15.06.2024.
//

#include <utility>

#include "../../include/Scene/KittiObject.h"

void KittiObject::render(cv::InputOutputArray &img) {
    this->label.getBoundingBox().render(img);
}

void KittiObject::setColor(const cv::Scalar &color) {
    this->label.getBoundingBox().setColor(color);
}

void KittiObject::setColor(int r, int g, int b) {
    this->setColor(cv::Scalar(r, g, b));
}

bool KittiObject::processClicks(int x, int y) {
    return this->label.getBoundingBox().getClicked(x, y);
}

Label KittiObject::getLabel() const {
    return label;
}

KittiObject::KittiObject(Label label) : label(std::move(label)) {}

KittiObject::KittiObject() = default;

bool KittiObject::operator==(KittiObject &other){
    return (label.getBoundingBox().getTopLeft().getX() == other.label.getBoundingBox().getTopLeft().getX()) 
            && (label.getBoundingBox().getTopLeft().getY() == other.label.getBoundingBox().getTopLeft().getY())
            && (label.getBoundingBox().getBottomRight().getX() == other.label.getBoundingBox().getBottomRight().getX())
            && (label.getBoundingBox().getBottomRight().getY() == other.label.getBoundingBox().getBottomRight().getY()) ;
}
