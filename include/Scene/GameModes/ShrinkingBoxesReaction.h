#ifndef REACTIONGAME_SHRINKINGBOXESREACTION_H
#define REACTIONGAME_SHRINKINGBOXESREACTION_H

#include "DirectClickReaction.h"
#include "..\HelperClasses\Point.h"


class ShrinkingBoxesReaction : public DirectClickReaction {
private:
    helper::Point initialRandomObjTopLeft;
    helper::Point initialRandomObjBottomRight;
    int deltaX, deltaY=0;
    const double shrinkingTimeDiff = 0.25;
    std::chrono::_V2::system_clock::time_point lastShrunkTimePoint;

    void doWhileWaitingOnInput() override;

    void makeRandomObjVisible() override;

    void calcDeltaX();
    
    void calcDeltaY();

    void setCopyAsNewImg(Frame& frame);

public:
    ShrinkingBoxesReaction(int pNumberOfFrames, int pSequence);    

};

#endif //REACTIONGAME_SHRINKINGBOXESREACTION_H
