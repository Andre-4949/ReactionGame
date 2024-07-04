#include "../Scenery.h"

#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H


class DirectClickReaction : public Scenery {
    bool waitingOnClick = false;
public:
    explicit DirectClickReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    void update() override;

    ~DirectClickReaction();
};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H