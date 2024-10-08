#ifndef REACTIONGAME_LABEL_H
#define REACTIONGAME_LABEL_H

#include <utility>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "GTBoundingBox.h"

class Label
{
private:
	[[maybe_unused]] int m_frame;            //Frame number, where the bounding box corresponds to
	std::string m_type;     //Class of the bounding box (e.g. Pedestrian, Car, Cyclist) --> DontCare should be ignored

	GTBoundingBox boundingBox;
public:
	Label(): m_frame(0), m_type(""), boundingBox(cv::Rect())
	{}

	Label(const int frame, const std::string type, const GTBoundingBox bbox): m_frame(frame), m_type(std::move(type)),
																									  boundingBox(std::move(bbox))
	{}

	static std::vector<Label> loadLabelsFromFile(const std::string & filename);

	[[nodiscard]] const std::string & getMType() const;

	[[nodiscard]] int getMFrame() const;

	GTBoundingBox & getBoundingBox();
};

#endif //REACTIONGAME_LABEL_H