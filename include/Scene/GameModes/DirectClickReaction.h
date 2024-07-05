#include "../Scenery.h"

#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H


class DirectClickReaction : public Scenery {
public:
    explicit DirectClickReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    // void update() override;

    void makeRandomObjVisible() override;

    void setupFrame() override;

    ~DirectClickReaction();

};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H