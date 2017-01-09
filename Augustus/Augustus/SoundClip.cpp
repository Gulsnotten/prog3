#include "stdafx.h"
#include "SoundClip.h"


const int SoundClip::INVALID_CHANNEL = -1;

SoundClip::SoundClip(Mix_Chunk* p_mix)
	: m_clip(p_mix)
{
	m_lastChannel = INVALID_CHANNEL;
}

SoundClip::~SoundClip()
{
}

void SoundClip::Play()
{
	m_lastChannel = Mix_PlayChannel(-1, m_clip, 0);
}

void SoundClip::PlayLooped()
{
	m_lastChannel = Mix_PlayChannel(-1, m_clip, -1);
}

void SoundClip::Stop()
{
	if (m_lastChannel != INVALID_CHANNEL) {
		if (Mix_Playing(m_lastChannel)) {
			Mix_HaltChannel(m_lastChannel);
		}
	}
}

void SoundClip::Pause()
{
	if (m_lastChannel != INVALID_CHANNEL) {
		if (!Mix_Paused(m_lastChannel)) {
			Mix_Pause(m_lastChannel);
		}
	}
}

void SoundClip::Resume()
{
	if (m_lastChannel != INVALID_CHANNEL) {
		if (Mix_Paused(m_lastChannel)) {
			Mix_Resume(m_lastChannel);
		}
	}
}


void SoundClip::SetVolume(float p_volume)
{
	int volume = int(p_volume * 128);

	if (volume > MIX_MAX_VOLUME) {
		volume = MIX_MAX_VOLUME;
	}
	
	if (volume < 0) {
		volume = 0;
	}

	m_clip->volume = volume;
}

bool SoundClip::IsPlaying()
{
	return (Mix_Playing(m_lastChannel) == 1);
}
