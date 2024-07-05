#include "../../../include/Scene/GameModes/EveryObjectReaction.h"

EveryObjectReaction::EveryObjectReaction(int pNumberOfFrames, int pSequence) : DirectClickReaction(pNumberOfFrames,
                                                                                                   pSequence) {
    Frame::labelFilter = {Labeltypes::CAR, Labeltypes::DONTCARE, Labeltypes::VAN, Labeltypes::CYCLIST,
                          Labeltypes::PEDESTRIAN};
}
