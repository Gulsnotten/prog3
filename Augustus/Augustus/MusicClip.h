#pragma once

class MusicClip // In its own .h and .cpp file
{
public:
	MusicClip(Mix_Music* p_clip);
	~MusicClip();

	void Play();
	void PlayLooped();
	void Stop();

	void Pause();
	void Resume();

	void SetVolume(float p_volume); // 0 is silent, 1f is max volume

	bool IsPlaying();
private:
	Mix_Music* m_clip;
};