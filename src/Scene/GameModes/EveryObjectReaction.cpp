#include "../../../include/Scene/GameModes/EveryObjectReaction.h"

EveryObjectReaction::EveryObjectReaction(const int pNumberOfFrames, const int pSequence): DirectClickReaction(pNumberOfFrames,
																																				  pSequence)
{
	Frame::labelFilter = Labeltypes::ALL_LABELS;
}
