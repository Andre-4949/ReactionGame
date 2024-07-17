#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H

#include "../GameMode.h"

class DirectClickReaction : public GameMode {
    void processClicks(const int x,const int y) override;

public:
    explicit DirectClickReaction(int pNumberOfFrames, int pSequence);

    void makeRandomObjVisible() override;
    
};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H