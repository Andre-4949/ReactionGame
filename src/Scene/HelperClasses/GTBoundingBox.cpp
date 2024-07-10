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
    cv::rectangle(img, topLeft, bottomRight, color, 2);
}

GTBoundingBox::GTBoundingBox(cv::Rect rect) : Rect_(rect) {
    this->topLeft = helper::Point(rect.x, rect.y);
    this->bottomRight = helper::Point(rect.x + rect.width, rect.y + rect.height);
    this->center = helper::Point(rect.x + (rect.width/2), rect.y + (rect.height/2));
}

GTBoundingBox::GTBoundingBox(int x, int y, int width, int height) : Rect_(x, y, width, height) {
    this->topLeft = helper::Point(x, y);
    this->bottomRight = helper::Point(x + width, y + height);
    this->center = helper::Point(x + (width/2), y + (height/2));

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
    return this->topLeft;
}

helper::Point GTBoundingBox::getBottomRight() {
    return this->bottomRight;
}

helper::Point GTBoundingBox::getCenter() {
    return center;
}

bool GTBoundingBox::equals(GTBoundingBox b) {
    return this->topLeft.equals(b.topLeft) && this->bottomRight.equals(b.bottomRight);
}

void GTBoundingBox::setTopLeft(int x, int y){
    this->x = x;
    this->y = y;
    this->topLeft = helper::Point(x, y);
}

void GTBoundingBox::setBottomRight(int x, int y){
    this->bottomRight = helper::Point(x, y);
}