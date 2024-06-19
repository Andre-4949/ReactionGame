//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_POINT_H
#define REACTIONGAME_POINT_H

class Point {
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) {};
    bool greaterXY(int x, int y);
    bool smallerXY(int x, int y);
};

#endif //REACTIONGAME_POINT_H
