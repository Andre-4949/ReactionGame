#include "../../include/Scene/ResultsHandler.h"
#include <algorithm>
#include <iostream>

ResultsHandler::ResultsHandler(std::string pName) : name(pName) {
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

    int index3 = sortedTimes.size() >= 3 ? 3 : (int) sortedTimes.size();

    std::vector<double> newBest3Times(sortedTimes.begin(), sortedTimes.begin() + index3);
    best3Times = newBest3Times;
}

void ResultsHandler::printResults() {
    std::cout << "Das Spiel ist vorbei! Hier deine Daten: " << std::endl;
    std::cout << "Deine durschnittliche Reaktionszeit: " << avgTime << " Sekunden" << std::endl;
    std::cout << "Deine " << best3Times.size() << " besten Zeiten: " << std::endl;
    for (int i = 0; i < best3Times.size(); i++) {
        std::cout << i + 1 << ". " << best3Times[i] << " Sekunden" << std::endl;
    }
}

void ResultsHandler::addTime(double time_in_seconds)
{
    times.push_back(time_in_seconds);
}
