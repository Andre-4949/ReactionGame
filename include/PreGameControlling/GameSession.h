
#ifndef REACTIONGAME_GAMESESSION_H
#define REACTIONGAME_GAMESESSION_H

#include <string>
#include "../Scene/GameMode.h"

class GameSession
{
private:
	bool gameSessionRunning = true;
	GameMode* scene = nullptr;
	std::string name;
	std::string windowName = "ReactionGame";

	void render();

	void update();

public:
	GameSession() = default;

	GameSession(GameMode* pScene, std::string pName);

	void loop();

	void mouseEvents(const int event, const int x, const int y, const int flags, void* userdata) const;

	GameMode* getGameMode() const;

	const std::string & getWindowName() const;

	const cv::Mat & getCurrentImg() const;

	void setGameSessionRunning(const bool gameSessionRunning);
};

#endif //REACTIONGAME_GAMESESSION_H
