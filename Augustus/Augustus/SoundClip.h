#pragma once

class SoundClip // In its own .h and .cpp file
{
public:
	SoundClip(Mix_Chunk* p_mix);
	~SoundClip();

	void Play(); // Example: Plays the Mix_Chunk and stores the channel returned in m_iLastChannelPlayed
	void PlayLooped();
	void Stop(); // Example: If m_iLastChannelPlayed is not an invalid value, and sound is still playing. Stop it.
				 // Other functionality to implement could be sound levels, looping, etc.

	void Pause();
	void Resume();

	void SetVolume(float p_volume); // 0 is silent, 1f is max volume

	bool IsPlaying();
private:
	Mix_Chunk* m_clip;
	int m_lastChannel;

	static const int INVALID_CHANNEL;
};