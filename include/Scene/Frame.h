//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_FRAME_H
#define REACTIONGAME_FRAME_H


#include <vector>
#include "KittiObject.h"
#include "./HelperClasses/Labeltypes.h"
#include <unordered_set>
class Frame {
private:
    std::vector<KittiObject> objects;
    int indexOfRandomObject;
    cv::Mat img;
public:
    static inline std::unordered_set<std::string> labelFilter = {Labeltypes::CAR};
    Frame();

    Frame(std::vector<Label> labels, cv::Mat img, int imageNumber);

    void setObjects(const std::vector<KittiObject> &objects);

    void render();

    std::vector<KittiObject> processClicks(int x, int y);

    void chooseRandomObject();

    void setAllKittiObjectVisible();

    void setAllKittiObjectInvisible();

    const std::vector<KittiObject> &getObjects() const;

    const int getRandomlySelectedObject() const;

    GTBoundingBox &getBoundingBoxOfRandomObject();

    void setColorOfAllObjects(cv::Scalar color);

    void setImg(const cv::Mat &img);

    const cv::Mat &getImg() const;

    const std::unordered_set<std::string> &getLabelFilter() const;

    void setLabelFilter(const std::unordered_set<std::string> &labelFilter);
};


#endif //REACTIONGAME_FRAME_H
