#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H

#include "../GameMode.h"

class DirectClickReaction : public GameMode {
public:
    explicit DirectClickReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    void makeRandomObjVisible() override;

};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H