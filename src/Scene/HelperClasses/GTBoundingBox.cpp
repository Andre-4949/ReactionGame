//
// Created by andre on 15.06.2024.
//

#include "../../../include/Scene/HelperClasses/GTBoundingBox.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../../../include/PreGameControlling/Game.h"

bool GTBoundingBox::getClicked(int x, int y) {
    return this->contains(cv::Point(x, y));
}

void GTBoundingBox::render() {
    if (!this->isVisible)return;
    cv::Mat img = Game::session.getScene()->getFrames().front().getImg();
    cv::rectangle(img, topLeft, bottomRight, color, 3);
}

GTBoundingBox::GTBoundingBox(cv::Rect rect) : Rect_(rect) {
    this->topLeft = helper::Point(rect.x, rect.y);
    this->topRight = helper::Point(rect.x + rect.width, rect.y);
    this->bottomLeft = helper::Point(rect.x, rect.y + rect.height);
    this->bottomRight = helper::Point(rect.x + rect.width, rect.y + rect.height);
}

GTBoundingBox::GTBoundingBox(int x, int y, int width, int height) : Rect_(x, y, width, height) {
    this->topLeft = helper::Point(x, y);
    this->topRight = helper::Point(x + width, y);
    this->bottomLeft = helper::Point(x, y + height);
    this->bottomRight = helper::Point(x + width, y + height);
}

const cv::Scalar &GTBoundingBox::getColor() const {
    return color;
}

void GTBoundingBox::setColor(const cv::Scalar &color) {
    this->color = color;
}

bool GTBoundingBox::getIsVisible() const {
    return isVisible;
}

void GTBoundingBox::setVisible(bool newVisible) {
    this->isVisible = newVisible;
}

helper::Point GTBoundingBox::getTopLeft() {
    return topLeft;
}

helper::Point GTBoundingBox::getBottomRight() {
    return bottomRight;
}
