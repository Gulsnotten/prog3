#include "stdafx.h"
#include "MusicClip.h"




MusicClip::MusicClip(Mix_Music * p_clip)
	: m_clip(p_clip)
{
}

MusicClip::~MusicClip()
{
}

void MusicClip::Play()
{
	Mix_PlayMusic(m_clip, 0);
}

void MusicClip::PlayLooped()
{
	Mix_PlayMusic(m_clip, -1);
}

void MusicClip::Stop()
{
	Mix_HaltMusic();
}

void MusicClip::Pause()
{
	Mix_PauseMusic();
}

void MusicClip::Resume()
{
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}


void MusicClip::SetVolume(float p_volume)
{
	int volume = int(p_volume * 128);

	if (volume > MIX_MAX_VOLUME) {
		volume = MIX_MAX_VOLUME;
	}

	if (volume < 0) {
		volume = 0;
	}

	Mix_VolumeMusic(volume);
}

bool MusicClip::IsPlaying()
{
	return Mix_PlayingMusic() == 1;
}
