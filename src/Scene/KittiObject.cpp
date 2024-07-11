#include <utility>

#include "../../include/Scene/KittiObject.h"
#include "../../include/PreGameControlling/Game.h"

void KittiObject::render() {
    this->label.getBoundingBox().render();
}

void KittiObject::setColor(const cv::Scalar &color) {
    this->label.getBoundingBox().setColor(color);
}

void KittiObject::setColor(int r, int g, int b) {
    this->setColor(cv::Scalar(b, g, r));
}

bool KittiObject::processClicks(int x, int y) {
    return this->label.getBoundingBox().getClicked(x, y);
}

Label &KittiObject::getLabel() {
    return this->label;
}

KittiObject::KittiObject(Label label) : label(std::move(label)) {}

KittiObject::KittiObject() = default;

bool KittiObject::operator==(KittiObject &other) {
    return label.getBoundingBox() == other.getLabel().getBoundingBox();
}
