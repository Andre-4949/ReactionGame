#include "../Scenery.h"

#ifndef REACTIONGAME_DIRECTCLICKREACTION_H
#define REACTIONGAME_DIRECTCLICKREACTION_H


class DirectClickReaction : public Scenery {
public:
    explicit DirectClickReaction(int pNumberOfFrames, int pSequence);

    void processClicks(int x, int y) override;

    // void update() override;

    virtual void makeRandomObjVisible() override;

    void setupFrame() override;

    ~DirectClickReaction();

    virtual void onPlayerClickedCorrect(int x, int y) override;

    virtual void onPlayerMissedClick(int x, int y) override;

};


#endif //REACTIONGAME_DIRECTCLICKREACTION_H