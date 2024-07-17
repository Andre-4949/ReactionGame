#ifndef REACTIONGAME_COLORCHANGEREACTION_H
#define REACTIONGAME_COLORCHANGEREACTION_H

#include "../GameMode.h"

class ColorChangeReaction : public GameMode
{
private:
	std::vector<KittiObject> selectedObjs;
	helper::Point clickedPoint;

	void processClicks(const int x, const int y) override;

	void processSpaceBarInput();

	void setupFrame() override;

	void makeRandomObjVisible() override;

public:
	explicit ColorChangeReaction(const int pNumberOfFrames, const int pSequence);
};

#endif //REACTIONGAME_COLORCHANGEREACTION_H