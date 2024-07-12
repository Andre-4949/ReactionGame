#include "gtest/gtest.h"
#include "../include/Scene/Scenery.h"
#include "../include/Scene/GameModes/DirectClickReaction.h"
#include "../include/HelperClasses/Utils.h"

/**
 * Known objects in Frames/Sequence:
 * sequence 0 image 0:
 * - DontCare, Van, Cyclist, Pedestrian
 * sequence 1 image 0:
 * - Car, DontCare
 * */
class FrameTest : public ::testing::Test {
protected:
    std::list<std::string> labelsToFind;
    Frame frame;

    Frame getFrame(int sequence, int frameNum) {
        std::string labelsPath = Util::fileUtil::generateLabelFolderPath(sequence);
        std::vector<Label> labels = Label::loadLabelsFromFile(labelsPath);
        std::string imagePath = Util::fileUtil::generateImagePath(frameNum, sequence);
        return {labels, cv::imread(imagePath), frameNum};
    }

    std::list<std::string> unorderedSetToList(const std::unordered_set<std::string> set) {
        std::list<std::string> list;
        for (const auto &item: set) {
            list.push_back(item);
        }
        return list;
    }

    void removeLabelForImg(int frameNum, int sequence) {
        Frame::labelFilter = Labeltypes::ALL_LABELS;
        frame = getFrame(sequence, frameNum);
        ASSERT_FALSE(frame.getObjects().empty());
        for (auto &item: frame.getObjects()) {
            labelsToFind.remove(item.getLabel().getMType());
        }
    }
};

TEST_F(FrameTest, FilterTest) {
    labelsToFind = unorderedSetToList(Labeltypes::ALL_LABELS);
    removeLabelForImg(0, 1);
    removeLabelForImg(0, 0);
    for (const auto &item: labelsToFind) {
        if (!item.empty())std::cout << item << std::endl;
        ASSERT_TRUE(item.empty());
    }
}

TEST_F(FrameTest, getObjectsOfTypeTest) {
    for (const auto &label: Labeltypes::ALL_LABELS) {
        std::vector<KittiObject> controlVector;
        std::vector<KittiObject> providedVector = frame.getObjectsOfType(label);
        for (auto &kittiObject: frame.getObjects()) {
            if (kittiObject.getLabel().getMType() == label) {
                controlVector.push_back(kittiObject);
            }
        }
        controlVector.shrink_to_fit();
        providedVector.shrink_to_fit();
        EXPECT_EQ(controlVector.size(), providedVector.size());
        for (int i = 0; i < providedVector.size(); ++i) {
            ASSERT_TRUE(controlVector[i] == providedVector[i]);
        }
    }
}

TEST_F(FrameTest, ColorTest) {
    std::string label = Labeltypes::PEDESTRIAN;
    std::vector<KittiObject> uncoloredObj = frame.getObjects();
    frame.setColorOfAllObjects(cv::Scalar(0,0,0));
    frame.colorObjectsOfType(label, cv::Scalar(1, 1, 1));
    for (int i = 0; i < uncoloredObj.size(); ++i) {
        if(frame.getObjects()[i].getLabel().getBoundingBox().getColor()!=uncoloredObj[i].getLabel().getBoundingBox().getColor()){
            EXPECT_EQ(uncoloredObj[i].getLabel().getMType(),label);
        }
    }
    frame.colorObjectsOfType(label,cv::Scalar(0,0,0));
    for (int i = 0; i < uncoloredObj.size(); ++i) {
        EXPECT_EQ(frame.getObjects()[i].getLabel().getBoundingBox().getColor(),uncoloredObj[i].getLabel().getBoundingBox().getColor());
    }
}

TEST_F(FrameTest, MakeKittiObjectsInvisibleTest){
    frame.setAllKittiObjectsInvisible();
    for (auto &item: frame.getObjects()){
        ASSERT_FALSE(item.getLabel().getBoundingBox().getIsVisible());
    }


    frame.setAllKittiObjectsVisible();
    for (auto &item: frame.getObjects()){
        ASSERT_TRUE(item.getLabel().getBoundingBox().getIsVisible());
    }
}