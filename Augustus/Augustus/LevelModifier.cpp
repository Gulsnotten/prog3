#include "stdafx.h"
#include "LevelModifier.h"

#include "Config.h"

LevelModifier::LevelModifier()
{
	PacSpeed = Config::MOVEMENT_SPEED;
	GhostSpeed = Config::MOVEMENT_SPEED;
	FleeingTime = Config::FLEEING_TIME;
	IgnoreEnergizer = false;
}

LevelModifier::LevelModifier(float p_pacSpeed, float p_ghostSpeed, float p_fleeingTime, bool p_ignoreEnergizer)
	: PacSpeed(p_pacSpeed), GhostSpeed(p_ghostSpeed),
	FleeingTime(p_fleeingTime), IgnoreEnergizer(p_ignoreEnergizer)
{
}

LevelModifier LevelModifier::GetModifier(int p_level)
{
	LevelModifier ret = LevelModifier();

	if (p_level > Config::ENERGIZER_STOP_AT) {
		ret.IgnoreEnergizer = true;
	}

	//if ()

	return ret;
}
