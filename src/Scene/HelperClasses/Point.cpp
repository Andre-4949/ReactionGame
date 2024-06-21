//
// Created by andre on 15.06.2024.
//

#include "../../../include/Scene/HelperClasses/Point.h"

bool Point::greaterXY(int x, int y) {
    return (this->x < x) && (this->y < y);
}

bool Point::smallerXY(int x, int y) {
    return (this->x > x) && (this->y > y);
}
