#include "gtest/gtest.h"
#include "../include/Scene/HelperClasses/GTBoundingBox.h"
#include "opencv2/opencv.hpp"

class GTBoundingBoxTest : public ::testing::Test{
protected:
    GTBoundingBox box = GTBoundingBox(0,0,10,10);
    GTBoundingBox box1= GTBoundingBox(box);
    cv::Rect rect = cv::Rect(0,0,10,10);
    helper::Point calculateCenter(){
        helper::Point center = box.getTopLeft();
        helper::Point bottomRight = box.getBottomRight();
        center.move(bottomRight.getX(),bottomRight.getY());
        center.setX(center.getX()/2);
        center.setY(center.getY()/2);
        return center;
    }
};


TEST_F(GTBoundingBoxTest, GTBoundingBoxConstructor) {
    ASSERT_TRUE(box.getTopLeft().equals(helper::Point(0,0)));
    ASSERT_TRUE(box.getBottomRight().equals(helper::Point(10,10)));
    ASSERT_TRUE(box.equals(box1));
    ASSERT_TRUE(box.equals(GTBoundingBox(rect)));
}

TEST_F(GTBoundingBoxTest, GTBoundingBoxMoveTest){
    box.moveTopLeft(10,10);
    ASSERT_TRUE(box.getTopLeft().equals(helper::Point(10,10)));
    box.moveBottomRight(-10,-10);
    ASSERT_TRUE(box.getBottomRight().equals(helper::Point(0,0)));
}

TEST_F(GTBoundingBoxTest, GTBoundingBoxVisibleTest){
    box.setVisible(false);
    ASSERT_FALSE(box.getIsVisible());
    box.setVisible(true);
    ASSERT_TRUE(box.getIsVisible());
}

TEST_F(GTBoundingBoxTest, GTBoundingBoxColorTest){
    cv::Scalar color = cv::Scalar(255,0,0);
    box.setColor(color);
    ASSERT_TRUE(box.getColor()==color);
}

TEST_F(GTBoundingBoxTest, GTBoundingBoxCenterTest){
    ASSERT_TRUE(calculateCenter().equals(box.getCenter()));
}

TEST_F(GTBoundingBoxTest, GTBoundingBoxGetClickedTest){
    helper::Point center = calculateCenter();
    ASSERT_TRUE(box.getClicked(center.getX(),center.getY()));
}
