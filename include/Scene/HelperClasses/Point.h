#ifndef REACTIONGAME_POINT_H
#define REACTIONGAME_POINT_H

#include "opencv2/opencv.hpp"

namespace helper {
    class Point{
        int x, y;
    public:
        Point(int x, int y);

        Point();

        void move(int x, int y);

        bool operator==(const Point p);

        int getX();

        int getY();

        void setX(int x);

        void setY(int y);

        cv::Point2i toCvPoint() const;
    };
}
#endif //REACTIONGAME_POINT_H
