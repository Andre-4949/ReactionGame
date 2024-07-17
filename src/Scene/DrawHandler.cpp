#include "../../include/Scene/DrawHandler.h"
#include "../../include/PreGameControlling/Game.h"

RelativePosition determinePointPositionHorizontal(const int distCenterX);

RelativePosition determinePointPositionVertical(const int distCenterY);

DrawHandler::DrawHandler() = default;

[[maybe_unused]] void DrawHandler::drawPlayerClickedCorrect(const int x, const int y, KittiObject &correctObj) {
    drawClickedPoint(x, y, Constants::GREEN);
    correctObj.setColor(Constants::GREEN);
};

[[maybe_unused]] void DrawHandler::drawPlayerMissedClick(const int x, const int y, KittiObject correctObj) {
    drawClickedPoint(x, y, Constants::RED);
    GTBoundingBox correctBox = correctObj.getLabel().getBoundingBox();
    drawDistToCorrectBox(x, y, correctBox);
};

void DrawHandler::drawClickedPoint(const int x, const int y, cv::Scalar color) {
    helper::Point clickedPoint = helper::Point(x, y);
    cv::circle(img, clickedPoint.toCvPoint(), 3, color, -1);
};


helper::Point calcVerticalIntersectionPoint(const double slope, const double yIntercept, const int boxX) {
    const int intersectionX = boxX;

    //y-value: y = m*x + c
    const int intersectionY = slope * boxX + yIntercept;

    return helper::Point(intersectionX, intersectionY);
}

helper::Point calcHorizontalIntersectionPoint(const double slope, const double yIntercept, const int boxY) {
    const int intersectionY = boxY;

    //x-value: y = m*x + c <=> x = (y - c)/m = (1/m)*(y - c)
    const double intersectionX = ((double)boxY - yIntercept) / slope;

    return helper::Point((int)intersectionX, intersectionY);
}

helper::Point
calcIntersectionPoint(const double slope, const double yIntercept, GTBoundingBox correctBox, const RelativePosition pointPosition) {
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

int calcBorderDistX(const int x, GTBoundingBox correctBox) {
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

int calcBorderDistY(const int y, GTBoundingBox correctBox) {
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
determinePointPosition(const int distNearestXBorder, const int distNearestYBorder, const int distCenterX, const int distCenterY, GTBoundingBox correctBox) {
    //line to box-center crosses horizontal border if point is above (imagined) diagonal line from center through nearest corner point
    //                                                     (or below if point is below the box)
    //slopes of these imagined lines = (+-boxHeight)/(+-boxWidth)
    const int boxWidth = correctBox.getBottomRight().getX() - correctBox.getTopLeft().getX();
    const int boxHeight = correctBox.getBottomRight().getY() - correctBox.getTopLeft().getY();
    if (distNearestXBorder * boxHeight > distNearestYBorder * boxWidth) {
        return determinePointPositionHorizontal(distCenterX);
    }
    return determinePointPositionVertical(distCenterY);
}

RelativePosition determinePointPositionVertical(const int distCenterY) {
    if (distCenterY > 0) {
        return top;
    }
    return bottom;
}

RelativePosition determinePointPositionHorizontal(const int distCenterX) {
    if (distCenterX > 0) {
        return left;
    }
    return right;
}

void DrawHandler::drawDistToCorrectBox(const int x, const int y, GTBoundingBox correctBox) {
    const int distNearestXBorder = calcBorderDistX(x, correctBox);
    const int distNearestYBorder = calcBorderDistY(y, correctBox);
    const int boxCenterX = correctBox.getCenter().getX();
    const int boxCenterY = correctBox.getCenter().getY();
    const int distCenterX = boxCenterX - x;
    const int distCenterY = boxCenterY - y;

    const RelativePosition pointPosition = determinePointPosition(distNearestXBorder, distNearestYBorder, distCenterX,
                                                            distCenterY, correctBox);

    //slope: m = (y1 - y2)/(x1 - x2)
    const double slope = ((distCenterY) / (double) distCenterX);

    //y-intercept: y = m*x + c ; P(x0,y0) on the line --> y0 = m*x0 + c <=> c = y0 - m*x0
    const double yIntercept = y - (slope * x);

    const helper::Point interSectionPoint = calcIntersectionPoint(slope, yIntercept, correctBox, pointPosition);

    cv::line(img, helper::Point(x, y).toCvPoint(), interSectionPoint.toCvPoint(), Constants::RED, 2);
};

void DrawHandler::setImg(const cv::Mat &img) {
    DrawHandler::img = img;
}