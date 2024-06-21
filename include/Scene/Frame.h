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
    KittiObject randomlySelectedObject;
public:
    //TODO Constructor

    void render(cv::InputOutputArray &img);
    std::vector<KittiObject> processClicks(int x, int y);
    void chooseRandomObject();

    void setAllKittiObjectVisible();
    void setAllKittiObjectInvisible();
    const std::vector<KittiObject> &getObjects() const;

    const KittiObject &getRandomlySelectedObject() const;
};


#endif //REACTIONGAME_FRAME_H
