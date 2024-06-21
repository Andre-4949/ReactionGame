#include "../Scenery.h"
#ifndef REACTIONGAME_COLORCHANGEREACTION_H
#define REACTIONGAME_COLORCHANGEREACTION_H


class ColorChangeReaction : public Scenery{
  public:
    ColorChangeReaction(int pNumberOfFrames);
    void processClicks() override;
};


#endif //REACTIONGAME_COLORCHANGEREACTION_H