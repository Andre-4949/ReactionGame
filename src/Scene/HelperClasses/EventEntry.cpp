//
// Created by andre on 15.06.2024.
//

#include <utility>

#include "../../../include/Scene/HelperClasses/EventEntry.h"

EventEntry::EventEntry(KittiObject obj, EventEntryType t, char value) : obj(std::move(obj)), type(t), value(value) {
    this->time = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

EventEntry::EventEntry(uint64_t time, KittiObject obj, EventEntryType type, char value) : time(time),
                                                                                          obj(std::move(obj)),
                                                                                          type(type), value(value) {}
