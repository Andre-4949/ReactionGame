#ifndef REACTIONGAME_EVERYOBJECTREACTION_H
#define REACTIONGAME_EVERYOBJECTREACTION_H

#include "DirectClickReaction.h"

class EveryObjectReaction : public DirectClickReaction {
public:
    EveryObjectReaction(const int pNumberOfFrames, const int pSequence);
};


#endif //REACTIONGAME_EVERYOBJECTREACTION_H
