//
// Created by andre on 15.06.2024.
//
#include <vector>
#include <string>
#ifndef REACTIONGAME_RESULTSHANDLER_H
#define REACTIONGAME_RESULTSHANDLER_H

class ResultsHandler {
  std::vector<double> times;
  std::string name;
  double avgTime;
  std::vector<double> best3Times;
public:
  ResultsHandler(std::string pName);
  void calcAvgTime();
  void calcBest3Times();
  void printResults();

};

#endif //REACTIONGAME_RESULTSHANDLER_H
