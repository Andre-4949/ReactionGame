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

    explicit GTBoundingBox(const cv::Rect rect);

    GTBoundingBox(const int x, const int y, const int width, const int height);

    void render();

    bool getClicked(const int x, const int y);

    [[nodiscard]] cv::Scalar getColor() const;

    void setColor(const cv::Scalar &color);

    void setVisible(const bool newVisible);

    helper::Point getTopLeft() const;

    helper::Point getBottomRight() const;

    void moveTopLeft(const int x, const int y);

    void moveBottomRight(const int x, const int y);

    helper::Point getCenter() const;

    [[nodiscard]] bool getIsVisible() const;

    bool operator==(GTBoundingBox b);
};


#endif //REACTIONGAME_GTBOUNDINGBOX_H
