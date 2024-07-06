#ifndef REACTIONGAME_SELECTCARSREACTION_H
#define REACTIONGAME_SELECTCARSREACTION_H


#include "ColorChangeReaction.h"

class SelectCarsReaction : public ColorChangeReaction {
public:
    SelectCarsReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    void makeRandomObjVisible() override;

    void loadLabels(int sequence) override;

    void showSolution();

    void paintSolution(std::vector<KittiObject> selectedObjs, int clickedX, int clickedY);

    void paintPlayerMissedClick(int x, int y);

    void paintPlayerClickedCar(std::vector<KittiObject> selectedObjs);
};


#endif //REACTIONGAME_SELECTCARSREACTION_H
