//
// Created by andre on 15.06.2024.
//

#ifndef REACTIONGAME_GTBOUNDINGBOX_H
#define REACTIONGAME_GTBOUNDINGBOX_H

#include <inttypes.h>
#include "Point.h"

class GTBoundingBox {
public:
    GTBoundingBox();

    Point topLeft=Point(0,0), topRight=Point(0,0), bottomLeft=Point(0,0), bottomRight=Point(0,0);
//    uint8_t rgbColor[3] = {0, 0, 0};

    //TODO Constructor
    void render();

    bool hasBeenClicked(int x, int y);
};


#endif //REACTIONGAME_GTBOUNDINGBOX_H
