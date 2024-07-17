#include "../../include/Scene/ResultsHandler.h"
#include <algorithm>
#include <iostream>

ResultsHandler::ResultsHandler(const std::string pName) : name(pName) {
}

void ResultsHandler::calcAvgTime() {
    double totalTime = 0.0;
    for (int i = 0; i < times.size(); i++) {
        totalTime += times[i];
    }
    avgTime = totalTime / times.size();
}

void ResultsHandler::calcBest3Times() {
    std::vector<double> sortedTimes = times;
    std::sort(sortedTimes.begin(), sortedTimes.end());

    //print out less times if less times were tracked
    int index3;
    if(sortedTimes.size() >= 3)
    {
        index3 = 3;
    }
    else{
        index3 = sortedTimes.size();
    }
    const std::vector<double> newBest3Times(sortedTimes.begin(), sortedTimes.begin() + index3);
    best3Times = newBest3Times;
}

void ResultsHandler::printResults() const {
    std::cout << "Das Spiel ist vorbei! Hier deine Daten: " << std::endl;
    std::cout << "Deine durchschnittliche Reaktionszeit: " << avgTime << " Sekunden" << std::endl;
    std::cout << "Deine " << best3Times.size() << " besten Zeiten: " << std::endl;
    for (int i = 0; i < best3Times.size(); i++) {
        std::cout << i + 1 << ". " << best3Times[i] << " Sekunden" << std::endl;
    }
}

void ResultsHandler::addTime(const double time_in_seconds) {
    times.push_back(time_in_seconds);
}
