#ifndef REACTIONGAME_GAMEMODE_H
#define REACTIONGAME_GAMEMODE_H

#include <vector>
#include "Frame.h"
#include "KittiObject.h"
#include "ResultsHandler.h"
#include "DrawHandler.h"
#include "queue"
#include "HelperClasses/Constants.h"
#include <chrono>
#include <unordered_map>

class GameMode
{
protected:
	[[maybe_unused]] int numberOfFrames = 0;
	int defaultTimeToWaitForOneFrame = Constants::SECONDSTOMILLISECONDS * 3;
	int sequence = 0;
	std::queue<Frame> frames = {};
	[[maybe_unused]] std::unordered_map<int, std::vector<Label>> currentLabels = {};
	ResultsHandler resultsHandler;
	DrawHandler drawHandler;
	[[maybe_unused]] static inline int currentFrameNumber = 0;
	std::chrono::_V2::system_clock::time_point showingObjTimePoint;
	bool waitingOnInput = false;
	double penaltyTime = 5.0;

	virtual void makeRandomObjVisible() = 0;

	[[maybe_unused]] void loadFrame(int frameNum);

	[[maybe_unused]] const bool checkAllFramesShown();

	virtual void setupFrame();

	[[maybe_unused]] virtual void loadLabels();

	virtual void evaluateInput(std::vector<KittiObject> & objects, int x, int y);

	[[maybe_unused]] virtual void doWhileWaitingOnInput();

	void saveTime(double time = -1);

public:
	GameMode(int pNumberOfFrames, int pSequence);

	virtual void update();

	void render();

	virtual void processClicks(const int x, const int y) = 0;

	void loadFrames();

	const ResultsHandler & getResultsHandler() const;

	const std::queue<Frame> & getFrames() const;

	std::vector<KittiObject> & getClickedObjects(const int x, const int y);
};

#endif //REACTIONGAME_GAMEMODE_H
