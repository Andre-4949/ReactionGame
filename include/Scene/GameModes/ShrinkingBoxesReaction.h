#ifndef REACTIONGAME_SHRINKINGBOXESREACTION_H
#define REACTIONGAME_SHRINKINGBOXESREACTION_H

#include "DirectClickReaction.h"
#include "..\HelperClasses\Point.h"


class ShrinkingBoxesReaction : public DirectClickReaction {
private:
  helper::Point initialRandomObjTopLeft;
  helper::Point initialRandomObjBottomRight;
  const double shrinkingTimeDiff = 0.25;
  std::chrono::_V2::system_clock::time_point lastShrinkedTimePoint;


public:
  ShrinkingBoxesReaction(int pNumberOfFrames, int pSequence);
  virtual void doWhileWaitingOnClick() override;
  void makeRandomObjVisible() override;
};

#endif //REACTIONGAME_SHRINKINGBOXESREACTION_H
