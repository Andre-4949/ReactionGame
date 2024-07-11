#include "../../../include/Scene/HelperClasses/GTBoundingBox.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../../../include/PreGameControlling/Game.h"

bool GTBoundingBox::getClicked(int x, int y) {
    return this->topLeft.getX() < x && this->topLeft.getY() < y && this->bottomRight.getX() > x && this->bottomRight.getY() > y;
}

void GTBoundingBox::render() {
    if (!this->isVisible)return;
    cv::Mat img = Game::session.getScene()->getFrames().front().getImg();
    cv::rectangle(img, topLeft.toCvPoint(), bottomRight.toCvPoint(), color, 2);
}

GTBoundingBox::GTBoundingBox(cv::Rect rect) {
    this->topLeft = helper::Point(rect.x, rect.y);
    this->bottomRight = helper::Point(rect.x + rect.width, rect.y + rect.height);
    this->center = helper::Point(rect.x + (rect.width/2), rect.y + (rect.height/2));
}

GTBoundingBox::GTBoundingBox(int x, int y, int width, int height) {
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

helper::Point &GTBoundingBox::getTopLeft() {
    return this->topLeft;
}

helper::Point GTBoundingBox::getBottomRight() {
    return this->bottomRight;
}

helper::Point GTBoundingBox::getCenter() {
    return center;
}

bool GTBoundingBox::operator==(GTBoundingBox b) {
    return this->topLeft == b.topLeft && this->bottomRight == b.bottomRight;
}

void GTBoundingBox::moveTopLeft(int x, int y){
    this->topLeft = helper::Point(this->topLeft.getX()+x, this->topLeft.getY()+y);
}

void GTBoundingBox::moveBottomRight(int x, int y){
    this->bottomRight = helper::Point(this->bottomRight.getX()+x, this->bottomRight.getY()+y);;
}