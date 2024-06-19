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
public:
    void render();
};


#endif //REACTIONGAME_FRAME_H
