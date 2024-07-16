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
    cv::Mat origImg;
public:
    static inline std::unordered_set<std::string> labelFilter = {Labeltypes::CAR};

    Frame();

    Frame(std::vector<Label> labels, cv::Mat img, int imageNumber);

    void setObjects(const std::vector<KittiObject> &objects);

    void render();

    std::vector<KittiObject> &processClicks(int x, int y);

    void chooseRandomObject();

    void setAllKittiObjectsVisible();

    void setAllKittiObjectsInvisible();

    std::vector<KittiObject> &getObjects();

    KittiObject& getRandomlySelectedObject();

    GTBoundingBox &getBoundingBoxOfRandomObject();

    void setColorOfAllObjects(cv::Scalar color);

    void setImg(const cv::Mat &img);

    const cv::Mat &getImg() const;

    const cv::Mat &getOriginalImg() const;

    void colorObjectsOfType(std::string type, cv::Scalar color);

    std::vector<KittiObject> getObjectsOfType(std::string type);
};


#endif //REACTIONGAME_FRAME_H
