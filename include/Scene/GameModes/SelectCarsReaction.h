#ifndef REACTIONGAME_SELECTCARSREACTION_H
#define REACTIONGAME_SELECTCARSREACTION_H

#include "ColorChangeReaction.h"

class SelectCarsReaction : public ColorChangeReaction {
public:
    SelectCarsReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    void makeRandomObjVisible() override;

    void showSolution();

    void drawPlayerMissedClick(int x, int y);

    void drawPlayerClickedCorrect(int x, int y);

    void paintPlayerClickedCar(std::vector<KittiObject> selectedObjs);

    void evaluateInput(std::vector<KittiObject> &objects, int x, int y);
};


#endif //REACTIONGAME_SELECTCARSREACTION_H
