//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_GTBOUNDINGBOX_H
#define REACTIONGAME_GTBOUNDINGBOX_H

#include <inttypes.h>
#include <opencv2/core/types.hpp>
#include "Point.h"


class GTBoundingBox : cv::Rect {
private:
    bool visible = false;
    helper::Point topLeft = helper::Point(0, 0);
    helper::Point topRight = helper::Point(0, 0);
    helper::Point bottomLeft = helper::Point(0, 0);
    helper::Point bottomRight = helper::Point(0, 0);
    cv::Scalar color = cv::Scalar(255, 0, 0);
public:

    GTBoundingBox(cv::Rect rect);

    GTBoundingBox(int x, int y, int width, int height);

    void render();

    bool getClicked(int x, int y);

    const cv::Scalar &getColor() const;

    void setColor(const cv::Scalar &color);

    bool isVisible() const;

    void setVisible(bool visible);

    helper::Point getTopLeft();
    helper::Point getBottomRight();
};


#endif //REACTIONGAME_GTBOUNDINGBOX_H
