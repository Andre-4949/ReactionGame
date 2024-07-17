#ifndef REACTIONGAME_CONSTANTS_H
#define REACTIONGAME_CONSTANTS_H

#include "opencv2/opencv.hpp"

class Constants{
public:
    static inline const int SECONDSTOMILLISECONDS = 1000;
    static inline const cv::Scalar BLUE = cv::Scalar(255, 0, 0);
    static inline const cv::Scalar GREEN = cv::Scalar(0, 255, 0);
    static inline const cv::Scalar RED = cv::Scalar(0, 0, 255);
    static inline const cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
};

#endif //REACTIONGAME_CONSTANTS_H
