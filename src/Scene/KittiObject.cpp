//
// Created by andre on 15.06.2024.
//

#include "../../include/Scene/KittiObject.h"

void KittiObject::render() {
    this->label.boundingBox.render();
}
