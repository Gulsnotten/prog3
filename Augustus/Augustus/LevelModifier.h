#pragma once

struct LevelModifier
{
	float PacSpeed;
	float GhostSpeed;
	float FleeingTime;
	bool IgnoreEnergizer;

	LevelModifier();
	LevelModifier(float p_pacSpeed, float p_ghostSpeed, float p_fleeingTime, bool p_ignoreEnergizer);

	LevelModifier GetModifier(int p_level);
};