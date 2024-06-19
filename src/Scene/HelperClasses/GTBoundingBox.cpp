//
// Created by andre on 15.06.2024.
//

#include "../../../include/Scene/HelperClasses/GTBoundingBox.h"

bool GTBoundingBox::hasBeenClicked(int x, int y) {
    return this->topLeft.greaterXY(x, y) and this->bottomRight.smallerXY(x, y);
}

void GTBoundingBox::render() {

}

GTBoundingBox::GTBoundingBox() {
}
