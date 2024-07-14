#ifndef REACTIONGAME_UTILS_H
#define REACTIONGAME_UTILS_H

#include <chrono>
#include <string>
#include <functional>
namespace Util {
    namespace fileUtil {
        std::string generateImgFolderPathString(int sequenceNr);

        std::string generateLabelFolderPath(int sequence);

        int getAmountOfFilesInFolder(std::string folderPath);

        std::string generateImagePath(int frameNum, int sequenceNum);

    };
    namespace stringUtil {
        std::string
        addStringUntilWidthIsReached(std::string originalStr, std::string stringToAppendOrInsert, int maxWidth);
    }
    namespace environmentalVar {
        void checkIfKittiPathIsSet();
    }

    namespace timing{
        void waitMilliSeconds(int time, std::function<bool(void)> breakCondition=[](){return false;}, std::function<void()> doWhileWaiting=[](){});
        double getTimeDifference(std::chrono::_V2::system_clock::time_point later, std::chrono::_V2::system_clock::time_point earlier);
    }

}
#endif //REACTIONGAME_UTILS_H
