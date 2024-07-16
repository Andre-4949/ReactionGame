#ifndef REACTIONGAME_DRAWHANDLER_H
#define REACTIONGAME_DRAWHANDLER_H

#include "HelperClasses/Constants.h"
#include "KittiObject.h"

enum RelativePosition{left, right, top, bottom};


class DrawHandler {
    cv::Mat img;
public:
    DrawHandler();
    ~DrawHandler();

    void drawPlayerMissedClick(int x, int y, KittiObject correctObj);

    void drawPlayerClickedCorrect(int x, int y, KittiObject &correctObj);

    void drawClickedPoint(int x, int y, cv::Scalar color);

    void drawDistToCorrectBox(int x, int y, GTBoundingBox correctObj);

    void setImg(const cv::Mat &img);


};

#endif //REACTIONGAME_DRAWHANDLER_H
