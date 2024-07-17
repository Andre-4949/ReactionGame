#ifndef REACTIONGAME_DRAWHANDLER_H
#define REACTIONGAME_DRAWHANDLER_H

#include "HelperClasses/Constants.h"
#include "KittiObject.h"

enum RelativePosition{left, right, top, bottom};


class DrawHandler {
    cv::Mat img;
public:
    DrawHandler();

    [[maybe_unused]] void drawPlayerMissedClick(const int x, const int y, KittiObject correctObj);

    [[maybe_unused]] void drawPlayerClickedCorrect(const int x, const int y, KittiObject &correctObj);

    void drawClickedPoint(const int x, const int y, cv::Scalar color);

    void drawDistToCorrectBox(const int x, const int y, GTBoundingBox correctObj);

    void setImg(const cv::Mat &img);

};

#endif //REACTIONGAME_DRAWHANDLER_H
