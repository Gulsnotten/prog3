#pragma once
 
//Suggested structure for a SoundManager

#include <map>
#include <vector>
#include <string>

#include "SoundClip.h"
#include "MusicClip.h"

class SoundClip;
class MusicClip;

class SoundManager
{
public:
	bool Initialize(); // Example: Initializes audio and opens channel if that is not done elsewhere
	void Shutdown(); // Example: Delete and clear all containers

	// Load sound from path, store loaded souns in soundchunks and create a new
	// soundclip and return it. The class creating the clip with the CreateSound
	// function should also destroy it using the DestroySound function. Also store
	// the SoundClip so that we can clean up everything we have created should we
	// be destroyed.
	SoundClip* CreateSound(const std::string& p_file);
	void DestroySound(SoundClip* m_pxSoundClip); // Destroy the clip, remove from vector of soundclip

	MusicClip* CreateMusic(const std::string& p_file);
	void DestroyMusic(MusicClip* p_clip); // Destroy the clip, remove from vector of soundclip

private:
	std::map<std::string, Mix_Chunk*> m_soundFiles;
	std::map<std::string, Mix_Music*> m_musicFiles;

	std::vector<SoundClip*> m_soundClips;
	std::vector<MusicClip*> m_musicClips;
};
