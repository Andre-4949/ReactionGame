#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H

#include "../Scenery.h"

class DirectClickReaction : public Scenery {
public:
    explicit DirectClickReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    virtual void makeRandomObjVisible() override;

    ~DirectClickReaction();

};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H