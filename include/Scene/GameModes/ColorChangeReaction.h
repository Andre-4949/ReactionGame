#include "../Scenery.h"

#ifndef REACTIONGAME_COLORCHANGEREACTION_H
#define REACTIONGAME_COLORCHANGEREACTION_H


class ColorChangeReaction : public Scenery {
private:
    std::vector<KittiObject> selectedObjs;
    helper::Point clickedPoint;
public:
    explicit ColorChangeReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    void processSpaceBarInput();


    void makeRandomObjVisible() override;

    void setupFrame() override;

    ~ColorChangeReaction();
};


#endif //REACTIONGAME_COLORCHANGEREACTION_H