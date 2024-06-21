#include "../Scenery.h"
#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H


class DirectClickReaction: public Scenery {
  public:
    DirectClickReaction(int pNumberOfFrames);
    void processClicks() override;
};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H