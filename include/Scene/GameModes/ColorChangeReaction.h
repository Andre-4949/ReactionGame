#ifndef REACTIONGAME_COLORCHANGEREACTION_H
#define REACTIONGAME_COLORCHANGEREACTION_H

#include "../GameMode.h"

class ColorChangeReaction : public GameMode {
private:
    std::vector<KittiObject> selectedObjs;
    helper::Point clickedPoint;
public:
    explicit ColorChangeReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    void processSpaceBarInput();

    void makeRandomObjVisible() override;

    void setupFrame() override;
};


#endif //REACTIONGAME_COLORCHANGEREACTION_H