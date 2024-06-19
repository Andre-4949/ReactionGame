//
// Created by andre on 14.06.2024.
//

#ifndef REACTIONGAME_LABEL_H
#define REACTIONGAME_LABEL_H

#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "GTBoundingBox.h"

class Label {
public:
    int m_frame;            //Frame number, where the bounding box corresponds to
    std::string m_type;     //Class of the bounding box (e.g. Pedestrian, Car, Cyclist) --> DontCare should be ignored
    cv::Rect m_bbox;
    GTBoundingBox boundingBox;
    Label() : m_frame(0), m_type(""), m_bbox(cv::Rect()) {}

    Label(int frame, const std::string &type, const cv::Rect &bbox) : m_frame(frame), m_type(type), m_bbox(bbox) {}


    static std::vector<Label> loadLabelsFromFile(std::string filename);
};

#endif //REACTIONGAME_LABEL_H
