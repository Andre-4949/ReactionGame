//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_POINT_H
#define REACTIONGAME_POINT_H

#include "opencv2/opencv.hpp"

namespace helper {
    class Point : public cv::Point2i {
        int x, y;
    public:
        Point(int x, int y);

        bool greaterXY(int x, int y) const;

        bool smallerXY(int x, int y);
        int getX();
        int getY();
    };
}
#endif //REACTIONGAME_POINT_H
