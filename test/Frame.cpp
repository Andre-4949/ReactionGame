#include "gtest/gtest.h"
#include "../include/Scene/Scenery.h"
#include "../include/Scene/GameModes/DirectClickReaction.h"


class FrameTest : public ::testing::Test {
protected:
    std::string labelsPath = Scenery::generateLabelFolderPath(0);
    std::vector<Label> labels = Label::loadLabelsFromFile(labelsPath);
    std::string imagePath = Scenery::generateImagePath(0,0);
    Frame frame;

//    void SetUp() override {
//        Frame::labelFilter
//        frame = Frame(labels,cv::imread(imagePath),0);
//    }
};

TEST_F(FrameTest, ConstructorTest){

}