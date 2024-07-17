#ifndef REACTIONGAME_RESULTSHANDLER_H
#define REACTIONGAME_RESULTSHANDLER_H

#include <vector>
#include <string>

class ResultsHandler {
    std::vector<double> times;
    std::string name;
    double avgTime;
    std::vector<double> best3Times;
public:
    ResultsHandler(std::string pName = "");

    void calcAvgTime();

    void calcBest3Times();

    void printResults() const;

    void addTime(double time_in_seconds);

};

#endif //REACTIONGAME_RESULTSHANDLER_H
