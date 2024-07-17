#ifndef REACTIONGAME_SELECTCARSREACTION_H
#define REACTIONGAME_SELECTCARSREACTION_H

#include "ColorChangeReaction.h"

class SelectCarsReaction : public ColorChangeReaction
{
	void processClicks(const int x, const int y) override;

	void makeRandomObjVisible() override;

	void drawPlayerMissedClick(const int x, const int y);

	void drawPlayerClickedCorrect(const int x, const int y);

	void evaluateInput(std::vector<KittiObject> & objects, const int x, const int y) override;

public:
	SelectCarsReaction(const int pNumberOfFrames, const int pSequence);
};

#endif //REACTIONGAME_SELECTCARSREACTION_H
