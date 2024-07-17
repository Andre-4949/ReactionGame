#ifndef REACTIONGAME_KITTIOBJECT_H
#define REACTIONGAME_KITTIOBJECT_H


#include "HelperClasses/Label.h"

class KittiObject {
    Label label;
public:
    KittiObject();

    explicit KittiObject(Label label);

    void render();

    void setColor(const cv::Scalar &color);

    const bool processClicks(const int x, const int y);

    Label &getLabel();

    bool operator==(KittiObject &other);

    bool operator!=(KittiObject &other);
};


#endif //REACTIONGAME_KITTIOBJECT_H
