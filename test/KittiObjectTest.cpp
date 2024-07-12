#include "gtest/gtest.h"
#include "../include/Scene/Scenery.h"

class KittiObjectTest : public ::testing::Test {
protected:
    std::string path = Scenery::generateLabelFolderPath(0);
    Label label = Label();
    KittiObject kittiObject = KittiObject();

    void SetUp() override {
        std::vector<Label> labels = Label::loadLabelsFromFile(path);
        label = labels[0];
        kittiObject = KittiObject(label);
    }
};

TEST_F(KittiObjectTest, KittiObjectConstructor) {
    ASSERT_TRUE(kittiObject.getLabel().getBoundingBox() == label.getBoundingBox());
    ASSERT_TRUE(kittiObject.getLabel().getMFrame() == label.getMFrame());
    ASSERT_TRUE(kittiObject.getLabel().getMType() == label.getMType());
}

TEST_F(KittiObjectTest, KittiObjectColorGetterAndSetter) {
    cv::Scalar color = cv::Scalar(255, 0, 0);
    kittiObject.setColor(0, 0, 255);
    ASSERT_TRUE(kittiObject.getLabel().getBoundingBox().getColor() == color);

    color = cv::Scalar(0, 0, 255);
    kittiObject.setColor(255,0,0);
    ASSERT_TRUE(kittiObject.getLabel().getBoundingBox().getColor() == color);

    color = cv::Scalar(0,255,0);
    kittiObject.setColor(0,255,0);
    ASSERT_TRUE(kittiObject.getLabel().getBoundingBox().getColor() == color);
}

TEST_F(KittiObjectTest, KittiObjectProcessClicks) {
    helper::Point center = kittiObject.getLabel().getBoundingBox().getCenter();
    helper::Point topLeft = kittiObject.getLabel().getBoundingBox().getTopLeft();
    helper::Point bottomRight = kittiObject.getLabel().getBoundingBox().getBottomRight();
    helper::Point topRight = helper::Point(bottomRight.getX(),topLeft.getY());
    helper::Point bottomLeft = helper::Point(topLeft.getX(),bottomRight.getY());

    ASSERT_TRUE(kittiObject.processClicks(center.getX(),center.getY()));
    ASSERT_FALSE(kittiObject.processClicks(topLeft.getX(),topLeft.getY()));
    ASSERT_FALSE(kittiObject.processClicks(bottomRight.getX(),bottomRight.getY()));
    ASSERT_FALSE(kittiObject.processClicks(topRight.getX(),topRight.getY()));
    ASSERT_FALSE(kittiObject.processClicks(bottomLeft.getX(),bottomLeft.getY()));
}