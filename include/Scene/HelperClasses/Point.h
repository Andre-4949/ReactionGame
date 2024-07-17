#ifndef REACTIONGAME_POINT_H
#define REACTIONGAME_POINT_H

#include "opencv2/opencv.hpp"

namespace helper
{
class Point
{
	int x, y;
public:
	Point(const int x, const int y);

	Point();

	void move(const int x, const int y);

	bool operator==(const Point p);

	const int getX() const;

	const int getY() const;

	void setX(const int x);

	void setY(const int y);

	cv::Point2i toCvPoint() const;
};
}
#endif //REACTIONGAME_POINT_H
