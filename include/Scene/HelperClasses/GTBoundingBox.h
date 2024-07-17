#ifndef REACTIONGAME_GTBOUNDINGBOX_H
#define REACTIONGAME_GTBOUNDINGBOX_H

#include <inttypes.h>
#include <opencv2/core/types.hpp>
#include "Point.h"


class GTBoundingBox {
private:
    bool isVisible = false;
    helper::Point topLeft = helper::Point(0, 0);
    helper::Point bottomRight = helper::Point(0, 0);
    helper::Point center = helper::Point(0, 0);
    cv::Scalar color = cv::Scalar(0, 0, 255);
public:

    GTBoundingBox(cv::Rect rect);

    GTBoundingBox(int x, int y, int width, int height);

    void render();

    bool getClicked(int x, int y);

    cv::Scalar getColor() const;

    void setColor(const cv::Scalar &color);

    void setVisible(bool newVisible);

    helper::Point getTopLeft();

    helper::Point getBottomRight();

    void moveTopLeft(int x, int y);

    void moveBottomRight(int x, int y);

    helper::Point getCenter();

    bool getIsVisible() const;

    bool operator==(GTBoundingBox b);
};


#endif //REACTIONGAME_GTBOUNDINGBOX_H
