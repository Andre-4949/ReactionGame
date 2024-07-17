#ifndef REACTIONGAME_UTILS_H
#define REACTIONGAME_UTILS_H

#include <chrono>
#include <string>
#include <functional>
namespace Util {
    namespace fileUtil {
        std::string generateImgFolderPathString(const int sequenceNr);

        std::string generateLabelFolderPath(const int sequence);

        int getAmountOfFilesInFolder(const std::string& folderPath);

        std::string generateImagePath(const int frameNum, const int sequenceNum);

    };
    namespace stringUtil {
        std::string
        addStringUntilWidthIsReached(std::string originalStr, const std::string& stringToAppendOrInsert, const int maxWidth);
    }
    namespace environmentalVar {
        void checkIfKittiPathIsSet();
    }

    namespace timing{
        void waitMilliSeconds(const int time, const std::function<bool(void)>& breakCondition=[](){return false;}, const std::function<void()>& doWhileWaiting=[](){});
        const double getTimeDifference(const std::chrono::_V2::system_clock::time_point later, const std::chrono::_V2::system_clock::time_point earlier);
    }

}
#endif //REACTIONGAME_UTILS_H
