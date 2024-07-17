#include "../../../include/Scene/HelperClasses/Point.h"

bool helper::Point::operator==(const helper::Point p)
{
	return this->x == p.x && this->y == p.y;
}

helper::Point::Point(const int x, const int y): x(x), y(y)
{
}

helper::Point::Point(): x(0), y(0)
{
}

void helper::Point::move(const int x, const int y)
{
	this->x += x;
	this->y += y;
}

const int helper::Point::getX() const
{
	return x;
}

const int helper::Point::getY() const
{
	return y;
}

void helper::Point::setX(const int x)
{
	this->x = x;
}

void helper::Point::setY(const int y)
{
	this->y = y;
}

cv::Point2i helper::Point::toCvPoint() const
{
	return cv::Point2i(this->x, this->y);
}
