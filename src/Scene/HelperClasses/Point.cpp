#include "../../../include/Scene/HelperClasses/Point.h"


bool helper::Point::equals(helper::Point p) {
    return this->x == p.x && this->y == p.y;
}


helper::Point::Point(int x, int y) : Point_(x, y), x(x), y(y) {
}

void helper::Point::move(int x, int y) {
    this->x += x;
    this->y += y;
}
