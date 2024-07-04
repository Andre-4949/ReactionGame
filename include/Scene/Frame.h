//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_FRAME_H
#define REACTIONGAME_FRAME_H


#include <vector>
#include "KittiObject.h"

class Frame {
private:
    std::vector<KittiObject> objects;
    int indexOfRandomObject;
    cv::Mat img;
public:
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

    void setImg(const cv::Mat &img);

    const cv::Mat &getImg() const;
};


#endif //REACTIONGAME_FRAME_H
