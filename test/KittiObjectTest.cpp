#include "gtest/gtest.h"
#include "../include/Scene/GameMode.h"
#include "../include/HelperClasses/Utils.h"
#include "../include/Scene/HelperClasses/Constants.h"

class KittiObjectTest : public ::testing::Test
{
protected:
	std::string path = Util::fileUtil::generateLabelFolderPath(0);
	Label label = Label();
	KittiObject kittiObject = KittiObject();

	void SetUp() override
	{
		std::vector<Label> labels = Label::loadLabelsFromFile(path);
		label = labels[0];
		kittiObject = KittiObject(label);
	}
};

TEST_F(KittiObjectTest, KittiObjectConstructor)
{
	ASSERT_TRUE(kittiObject.getLabel().getBoundingBox() == label.getBoundingBox());
	ASSERT_TRUE(kittiObject.getLabel().getMFrame() == label.getMFrame());
	ASSERT_TRUE(kittiObject.getLabel().getMType() == label.getMType());
}

TEST_F(KittiObjectTest, KittiObjectColorGetterAndSetter)
{
	cv::Scalar color = Constants::RED;
	kittiObject.setColor(Constants::RED);
	ASSERT_TRUE(kittiObject.getLabel().getBoundingBox().getColor() == color);
	color = Constants::BLUE;
	kittiObject.setColor(Constants::BLUE);
	ASSERT_TRUE(kittiObject.getLabel().getBoundingBox().getColor() == color);
	color = Constants::GREEN;
	kittiObject.setColor(Constants::GREEN);
	ASSERT_TRUE(kittiObject.getLabel().getBoundingBox().getColor() == color);
}

TEST_F(KittiObjectTest, KittiObjectProcessClicks)
{
	helper::Point center = kittiObject.getLabel().getBoundingBox().getCenter();
	helper::Point topLeft = kittiObject.getLabel().getBoundingBox().getTopLeft();
	helper::Point bottomRight = kittiObject.getLabel().getBoundingBox().getBottomRight();
	helper::Point topRight = helper::Point(bottomRight.getX(), topLeft.getY());
	helper::Point bottomLeft = helper::Point(topLeft.getX(), bottomRight.getY());
	ASSERT_TRUE(kittiObject.processClicks(center.getX(), center.getY()));
	ASSERT_TRUE(kittiObject.processClicks(topLeft.getX(), topLeft.getY()));
	ASSERT_TRUE(kittiObject.processClicks(bottomRight.getX(), bottomRight.getY()));
	ASSERT_TRUE(kittiObject.processClicks(topRight.getX(), topRight.getY()));
	ASSERT_TRUE(kittiObject.processClicks(bottomLeft.getX(), bottomLeft.getY()));
}