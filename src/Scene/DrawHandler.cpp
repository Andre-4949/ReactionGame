#include "../../include/Scene/DrawHandler.h"
#include "../../include/PreGameControlling/Game.h"

RelativePosition determinePointPositionHorizontal(int distCenterX);

RelativePosition determinePointPositionVertical(int distCenterY);

DrawHandler::DrawHandler() {

};

DrawHandler::~DrawHandler() {

};

void DrawHandler::drawPlayerClickedCorrect(int x, int y, KittiObject &correctObj) {
    drawClickedPoint(x, y, Constants::GREEN);
    correctObj.setColor(Constants::GREEN);
};

void DrawHandler::drawPlayerMissedClick(int x, int y, KittiObject correctObj) {
    drawClickedPoint(x, y, Constants::RED);
    GTBoundingBox correctBox = correctObj.getLabel().getBoundingBox();
    drawDistToCorrectBox(x, y, correctBox);
};

void DrawHandler::drawClickedPoint(int x, int y, cv::Scalar color) {
    helper::Point clickedPoint = helper::Point(x, y);
    cv::circle(img, clickedPoint.toCvPoint(), 3, color, -1);
};


helper::Point calcVerticalIntersectionPoint(double slope, double yIntercept, int boxX) {
    int intersectionX = boxX;

    //y-value: y = m*x + c
    int intersectionY = slope * boxX + yIntercept;

    return helper::Point(intersectionX, intersectionY);
}

helper::Point calcHorizontalIntersectionPoint(double slope, double yIntercept, int boxY) {
    int intersectionY = boxY;

    //x-value: y = m*x + c <=> x = (y - c)/m = (1/m)*(y - c)
    double intersectionX = ((double)boxY - yIntercept) / slope;

    return helper::Point((int)intersectionX, intersectionY);
}

helper::Point
calcIntersectionPoint(double slope, double yIntercept, GTBoundingBox correctBox, RelativePosition pointPosition) {
    switch (pointPosition) {
        case left:
            return calcVerticalIntersectionPoint(slope, yIntercept, correctBox.getTopLeft().getX());
        case right:
            return calcVerticalIntersectionPoint(slope, yIntercept, correctBox.getBottomRight().getX());
        case top:
            return calcHorizontalIntersectionPoint(slope, yIntercept, correctBox.getTopLeft().getY());
        case bottom:
            return calcHorizontalIntersectionPoint(slope, yIntercept, correctBox.getBottomRight().getY());
        default:
            std::cout << "Failed to properly calculate Intersection point!" << std::endl;
            return helper::Point();
    }
}

int calcBorderDistX(int x, GTBoundingBox correctBox) {
    //determine shorter distance to left or right border
    int distLeft = abs(x - correctBox.getTopLeft().getX());
    int distRight = abs(x - correctBox.getBottomRight().getX());
    int distBorderX = std::min(distLeft, distRight);

    //set distance to zero if point is between borders (on x-axis)
    bool isRightFromLeftBorder = x >= correctBox.getTopLeft().getX();
    bool isLeftFromRightBorder = x <= correctBox.getBottomRight().getX();
    if (isRightFromLeftBorder && isLeftFromRightBorder) distBorderX = 0;

    return distBorderX;
}

int calcBorderDistY(int y, GTBoundingBox correctBox) {
    //determine shorter distance to top or bottom border
    int distTop = abs(y - correctBox.getTopLeft().getY());
    int distBottom = abs(y - correctBox.getBottomRight().getY());
    int distBorderY = std::min(distTop, distBottom);

    //set distance to zero if point is between borders (on y-axis)
    bool isBelowTopBorder = y >= correctBox.getTopLeft().getY();
    bool isAboveBottomBorder = y <= correctBox.getBottomRight().getY();
    if (isBelowTopBorder && isAboveBottomBorder) distBorderY = 0;

    return distBorderY;
}

RelativePosition
determinePointPosition(int distNearestXBorder, int distNearestYBorder, int distCenterX, int distCenterY) {
    if (distNearestXBorder > distNearestYBorder) {
        return determinePointPositionHorizontal(distCenterX);
    }
    return determinePointPositionVertical(distCenterY);
}

RelativePosition determinePointPositionVertical(int distCenterY) {
    if (distCenterY > 0) {
        return top;
    }
    return bottom;
}

RelativePosition determinePointPositionHorizontal(int distCenterX) {
    if (distCenterX > 0) {
        return left;
    }
    return right;
}

void DrawHandler::drawDistToCorrectBox(int x, int y, GTBoundingBox correctBox) {
    int distNearestXBorder = calcBorderDistX(x, correctBox);
    int distNearestYBorder = calcBorderDistY(y, correctBox);
    int boxCenterX = correctBox.getCenter().getX();
    int boxCenterY = correctBox.getCenter().getY();
    int distCenterX = boxCenterX - x;
    int distCenterY = boxCenterY - y;

    RelativePosition pointPosition = determinePointPosition(distNearestXBorder, distNearestYBorder, distCenterX,
                                                            distCenterY);

    //slope: m = (y1 - y2)/(x1 - x2)
    double slope = ((distCenterY) / (double) distCenterX);

    //y-intercept: y = m*x + c ; P(x0,y0) on the line --> y0 = m*x0 + c <=> c = y0 - m*x0
    double yIntercept = y - (slope * x);

    helper::Point interSectionPoint = calcIntersectionPoint(slope, yIntercept, correctBox, pointPosition);

    cv::line(img, helper::Point(x, y).toCvPoint(), interSectionPoint.toCvPoint(), Constants::RED, 2);
};

void DrawHandler::setImg(const cv::Mat &img) {
    DrawHandler::img = img;
}