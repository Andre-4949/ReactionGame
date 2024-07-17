#ifndef REACTIONGAME_COLORCHANGEREACTION_H
#define REACTIONGAME_COLORCHANGEREACTION_H

#include "../GameMode.h"

class ColorChangeReaction : public GameMode {
private:
    std::vector<KittiObject> selectedObjs;
    helper::Point clickedPoint;

    void processClicks(int x, int y) override;

    void processSpaceBarInput();

    void setupFrame() override;

    void makeRandomObjVisible() override;

public:
    explicit ColorChangeReaction(int pNumberOfFrames, int pSequence);
};


#endif //REACTIONGAME_COLORCHANGEREACTION_H