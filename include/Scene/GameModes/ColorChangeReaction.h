#include "../Scenery.h"

#ifndef REACTIONGAME_COLORCHANGEREACTION_H
#define REACTIONGAME_COLORCHANGEREACTION_H


class ColorChangeReaction : public Scenery {
public:
    explicit ColorChangeReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    void update() override;

    ~ColorChangeReaction();

    void render() override;
};


#endif //REACTIONGAME_COLORCHANGEREACTION_H