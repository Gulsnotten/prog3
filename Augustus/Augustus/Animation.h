#pragma once
#include <vector>

class Sprite;
struct AnimationFrame;

class Animation
{
private:
	std::vector<AnimationFrame> m_frames;
public:
	Animation();
	Animation(std::vector<AnimationFrame> p_frames);
	~Animation();

	void AddFrame(AnimationFrame p_frame);

	int GetLength();
	Sprite* GetSprite(int p_time);
};


struct AnimationFrame { // length in milliseconds
	int m_length;
	Sprite* m_spritewPtr;

	AnimationFrame();
	AnimationFrame(Sprite* p_sprite, int p_length);

	static const AnimationFrame Empty;
};