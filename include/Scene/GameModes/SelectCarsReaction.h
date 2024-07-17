#ifndef REACTIONGAME_SELECTCARSREACTION_H
#define REACTIONGAME_SELECTCARSREACTION_H

#include "ColorChangeReaction.h"

class SelectCarsReaction : public ColorChangeReaction {
    void processClicks(int x, int y) override;

    void makeRandomObjVisible() override;

    void drawPlayerMissedClick(int x, int y);

    void drawPlayerClickedCorrect(int x, int y);

    void evaluateInput( std::vector<KittiObject> &objects, int x, int y) override;
public:
    SelectCarsReaction(int pNumberOfFrames, int pSequence);
};


#endif //REACTIONGAME_SELECTCARSREACTION_H
