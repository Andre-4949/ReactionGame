//
// Created by andre on 15.06.2024.
//

#include "../../../include/Scene/HelperClasses/GTBoundingBox.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

bool GTBoundingBox::getClicked(int x, int y) {
    return this->contains(cv::Point(x, y));
}

void GTBoundingBox::render(cv::InputOutputArray &img) {
    if(!visible)return;
    cv::line(img, topLeft, bottomLeft, color);
    cv::line(img, bottomLeft, bottomRight, color);
    cv::line(img, bottomRight, topRight, color);
    cv::line(img, topRight, topLeft, color);
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

bool GTBoundingBox::isVisible() const {
    return visible;
}

void GTBoundingBox::setVisible(bool visible) {
    this->visible = visible;
}
