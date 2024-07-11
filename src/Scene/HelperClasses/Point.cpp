#include "../../../include/Scene/HelperClasses/Point.h"


bool helper::Point::operator==(helper::Point p) {
    return this->x == p.x && this->y == p.y;
}


helper::Point::Point(int x, int y) : x(x), y(y) {
}

helper::Point::Point() : x(0), y(0) {
}

void helper::Point::move(int x, int y) {
    this->x += x;
    this->y += y;
}

int helper::Point::getX(){
    return x;
}

int helper::Point::getY(){
    return y;
}

void helper::Point::setX(int x){
    this->x = x;
}

void helper::Point::setY(int y){
    this->y = y;
}

cv::Point2i helper::Point::toCvPoint() {
    return cv::Point2i(this->x, this->y);
}
