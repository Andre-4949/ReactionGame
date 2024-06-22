//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_KITTIOBJECT_H
#define REACTIONGAME_KITTIOBJECT_H


#include "HelperClasses/Label.h"

class KittiObject {
    Label label;
public:
    KittiObject();
    explicit KittiObject(Label label);

    void render(cv::InputOutputArray &img);

    void setColor(const cv::Scalar &color);

    void setColor(int r, int g, int b);

    bool processClicks(int x, int y);

    Label getLabel() const;
};


#endif //REACTIONGAME_KITTIOBJECT_H
