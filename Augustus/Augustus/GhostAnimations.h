#pragma once
#include "Animation.h"
#include "vect2.h"
#include <vector>
#include "DirectionCollection.h"

class GhostAnimations
{
private:
	std::vector<DirectionCollection> m_colorAnimations;
	DirectionCollection m_deathCollection;
public:
	GhostAnimations();
	~GhostAnimations();

	Animation* GetAnimation(Vect2 p_dir, int p_index);
	Animation* GetDeathAnimation(Vect2 p_dir);

	Animation* BlueAnimation;
	Animation* WarningAnimation;
};