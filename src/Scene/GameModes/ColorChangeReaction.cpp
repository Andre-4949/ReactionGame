#include "../../../include/Scene/GameModes/ColorChangeReaction.h"
#include "../../../include/HelperClasses/Utils.h"
#include <random>

ColorChangeReaction::ColorChangeReaction(const int pNumberOfFrames, const int pSequence): GameMode(pNumberOfFrames, pSequence)
{
	Frame::labelFilter = {Labeltypes::CAR};
}

void ColorChangeReaction::processSpaceBarInput()
{

	//skip over function if user already clicked and pressed spacebar  --> !waitingOnInput
	if (frames.empty() || !waitingOnInput)return;
	waitingOnInput = false;
	Frame currentFrame = frames.front();
	KittiObject randomObj = currentFrame.getRandomlySelectedObject();
	randomObj.setColor(Constants::BLUE);
	evaluateInput(selectedObjs, clickedPoint.getX(), clickedPoint.getY());
}

void ColorChangeReaction::processClicks(const int x, const int y)
{
	if (frames.empty())
		return;
	selectedObjs = this->getClickedObjects(x, y);
	clickedPoint.setX(x);
	clickedPoint.setY(y);

	//wait 3 seconds for player to confirm input by pressing spacebar
	if ((char)cv::waitKey(3 * Constants::SECONDSTOMILLISECONDS) == ' ')
	{
		processSpaceBarInput();
		waitingOnInput = false;
	}
}

void ColorChangeReaction::makeRandomObjVisible()
{

	//wait random time between 1-2 seconds before drawing box around chosen object
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1 * Constants::SECONDSTOMILLISECONDS,
																					  2 * Constants::SECONDSTOMILLISECONDS);
	const int random_milliseconds = dist(rng);
	Util::timing::waitMilliSeconds(random_milliseconds);
	frames.front().getBoundingBoxOfRandomObject().setColor(Constants::RED);
}

void ColorChangeReaction::setupFrame()
{
	this->frames.front().setAllKittiObjectsVisible();
	this->frames.front().setColorOfAllObjects(Constants::BLUE);
	GameMode::setupFrame();
}