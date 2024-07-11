//
// Created by andre on 11.07.2024.
//
#include "../include/Scene/HelperClasses/Point.h"
#include "gtest/gtest.h"

class PointTest : public ::testing::Test{
protected:
    helper::Point point;
    int xToSet = 10;
    int yToSet = 10;
    void SetUp() override {
        point = helper::Point(xToSet,yToSet);
    }
};

TEST_F(PointTest, test0) {

    EXPECT_EQ(point.getX(),xToSet);
    EXPECT_EQ(point.getY(),yToSet);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}