#include "gtest/gtest.h"
#include "../include/Scene/Scenery.h"
#include "../include/HelperClasses/Utils.h"

class LabelTest : public ::testing::Test {
protected:
    std::string path = Util::fileUtil::generateLabelFolderPath(0);
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
