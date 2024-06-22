#include "../Scenery.h"

#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H


class DirectClickReaction : public Scenery {
public:
    explicit DirectClickReaction(int pNumberOfFrames);

    void processClicks() override;

    virtual ~DirectClickReaction();
};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H