#include "gtest/gtest.h"
#include "../include/Scene/Scenery.h"

class LabelTest : public ::testing::Test {
protected:
    std::string path = Scenery::generateLabelFolderPath(0);
    Label label = Label();

    void SetUp() override {
    }
};

TEST_F(LabelTest, DatasetIsEqual) {
    std::vector<Label> labels = Label::loadLabelsFromFile(path);
    ASSERT_FALSE(labels.empty());
    label = labels[0];
    EXPECT_EQ(label.getMType(), Labeltypes::DONTCARE);
    EXPECT_EQ(label.getMFrame(), 0);
}
