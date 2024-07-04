//
// Created by andre on 04.07.2024.
//

#ifndef REACTIONGAME_LABELTYPES_H
#define REACTIONGAME_LABELTYPES_H

#include <unordered_map>
#include <string>
#include <array>

//
class Labeltypes {
private:
    static inline std::array<std::string, 5> LABELTYPES = {
            "DontCare",
            "Van",
            "Cyclist",
            "Pedestrian",
            "Car"
    };
public:
    enum Labeltype {
        DONTCARE = 0, VAN = 1, CYCLIST = 2, PEDESTRIAN = 3, CAR = 4
    };

    static std::string toString(Labeltypes::Labeltype labelType);
};


#endif //REACTIONGAME_LABELTYPES_H
