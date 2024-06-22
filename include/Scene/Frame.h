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
    KittiObject randomlySelectedObject = KittiObject();
    cv::Mat img;
public:
    Frame();
    Frame(std::vector<Label> labels, cv::Mat img, int imageNumber);

    void setObjects(const std::vector<KittiObject> &objects);


    void render(cv::InputOutputArray &img);

    std::vector<KittiObject> processClicks(int x, int y);

    void chooseRandomObject();

    void setAllKittiObjectVisible();

    void setAllKittiObjectInvisible();

    const std::vector<KittiObject> &getObjects() const;

    const KittiObject &getRandomlySelectedObject() const;

    void setImg(const cv::Mat &img);
};


#endif //REACTIONGAME_FRAME_H
