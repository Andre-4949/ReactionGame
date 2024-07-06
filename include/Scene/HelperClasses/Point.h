#ifndef REACTIONGAME_POINT_H
#define REACTIONGAME_POINT_H

#include "opencv2/opencv.hpp"

namespace helper {
    class Point : public cv::Point2i {
        int x, y;
    public:
        Point(int x, int y);

        Point();

        void move(int x, int y);

        bool equals(helper::Point p);

        int getX();

        int getY();

        void setX(int x);

        void setY(int y);
    };
}
#endif //REACTIONGAME_POINT_H
