#ifndef REACTIONGAME_LABELTYPES_H
#define REACTIONGAME_LABELTYPES_H

#include <unordered_map>
#include <string>
#include <array>
#include <unordered_set>

class Labeltypes
{
public:
	//alphabetically sorted
	const static inline std::string CAR = "Car";
	const static inline std::string CYCLIST = "Cyclist";
	const static inline std::string DONTCARE = "DontCare";
	const static inline std::string PEDESTRIAN = "Pedestrian";
	const static inline std::string VAN = "Van";
	const static inline std::unordered_set<std::string> ALL_LABELS = {CAR, CYCLIST, DONTCARE, PEDESTRIAN, VAN};
};

#endif //REACTIONGAME_LABELTYPES_H
