//
// Created by andre on 15.06.2024.
//

#include "../../include/Scene/Scenery.h"

Scenery::Scenery(int pNumberOfFrames):numberOfFrames(pNumberOfFrames)
{
    
}

void Scenery::mouseEvents(int event, int x, int y, int flags, void *userdata) {

}

void Scenery::keyEvents() {

}

std::vector<KittiObject> Scenery::getClickedObjects(int x, int y) {
    return std::vector<KittiObject>();
}

void Scenery::render() {
    for (Frame &item: this->frames){
        item.render();
    }
}
