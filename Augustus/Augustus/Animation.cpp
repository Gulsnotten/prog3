#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
{
}

Animation::Animation(std::vector<AnimationFrame> p_frames)
	: m_frames(p_frames)
{
}


Animation::~Animation()
{
}

void Animation::AddFrame(AnimationFrame p_frame)
{
	m_frames.push_back(p_frame);
}

int Animation::GetLength()
{
	int ret = 0;

	for (auto f : m_frames) {
		ret += f.m_length;
	}

	return ret;
}

Sprite * Animation::GetSprite(int p_time)
{
	int time = p_time;

	unsigned int i = 0;
	if (time > 0) {
		while (time > 0) {
			assert(m_frames.size() > i); // make sure p_time is < GetLength in caller

			time -= m_frames[i].m_length;

			i++;
		}
		i--;
	}

	return m_frames[i].m_spritewPtr;
}


AnimationFrame::AnimationFrame()
{
}

AnimationFrame::AnimationFrame(Sprite* p_sprite, int p_length)
	: m_spritewPtr(p_sprite), m_length(p_length)
{

}
