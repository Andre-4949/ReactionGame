#include "../include/Scene/HelperClasses/Point.h"
#include "gtest/gtest.h"

class PointTest : public ::testing::Test
{
protected:
	helper::Point point;
	int xToSet = 10;
	int yToSet = 10;
	helper::Point point1;
	int xToSet2 = 20;
	int yToSet2 = 20;

	void SetUp() override
	{
		point = helper::Point(xToSet, yToSet);
		point1 = helper::Point(xToSet2, yToSet2);
	}
};

TEST_F(PointTest, PointGetterSetterTest)
{
	EXPECT_EQ(point.getX(), xToSet);
	EXPECT_EQ(point.getY(), yToSet);
}

TEST_F(PointTest, PointEqualsTest)
{
	ASSERT_TRUE(point == point);
}

TEST_F(PointTest, PointMoveTest)
{
	point.move(10, 10);
	ASSERT_TRUE(point == point1);
}

TEST_F(PointTest, PointCVPointConversion)
{
	cv::Point2i cvPoint = cv::Point2i(xToSet, yToSet);
	EXPECT_EQ(point.toCvPoint(), cvPoint);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}