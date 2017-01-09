#include "stdafx.h"
#include "SoundManager.h"

#include "SoundClip.h"
#include "MusicClip.h"

// reused the same code structure Jerry provided in SpriteManager.cpp

bool SoundManager::Initialize()
{
	return false;
}

void SoundManager::Shutdown()
{
	for (auto c : m_soundFiles) {
		Mix_FreeChunk(c.second);
	}
	for (auto m : m_musicFiles) {
		Mix_FreeMusic(m.second);
	}
}

SoundClip * SoundManager::CreateSound(const std::string & p_file)
{
	auto it = m_soundFiles.find(p_file); // Returns an iterator to a pos or end, depending on success
	if (it == m_soundFiles.end())
	{
		// If we do not find the mix we need to load it and inser it in to our std::map so
		// that we may create pointers to the same mix for several sounds.

		Mix_Chunk* xMix = Mix_LoadWAV(p_file.c_str());

		m_soundFiles.insert(std::pair<std::string, Mix_Chunk*>(p_file, xMix));

		it = m_soundFiles.find(p_file);
	}

	SoundClip* xSound = new SoundClip(it->second);

	m_soundClips.push_back(xSound);
	return xSound;
}

void SoundManager::DestroySound(SoundClip * m_pxSoundClip)
{
	for (unsigned int i = 0; i < m_soundClips.size(); i++) {
		SoundClip* s = m_soundClips[i];

		if (s == m_pxSoundClip) {
			delete s;
			s = nullptr;
			m_soundClips.erase(m_soundClips.begin() + 1); // delete from vector

			break;
		}
	}
}

MusicClip * SoundManager::CreateMusic(const std::string & p_file)
{
	auto it = m_musicFiles.find(p_file); // Returns an iterator to a pos or end, depending on success
	if (it == m_musicFiles.end())
	{
		// If we do not find the mix we need to load it and inser it in to our std::map so
		// that we may create pointers to the same mix for several sounds.

		Mix_Music* xMix = Mix_LoadMUS(p_file.c_str());

		m_musicFiles.insert(std::pair<std::string, Mix_Music*>(p_file, xMix));

		it = m_musicFiles.find(p_file);
	}

	MusicClip* xMusic = new MusicClip(it->second);

	m_musicClips.push_back(xMusic);
	return xMusic;
}

void SoundManager::DestroyMusic(MusicClip * p_clip)
{
	for (unsigned int i = 0; i < m_musicClips.size(); i++) {
		MusicClip* m = m_musicClips[i];

		if (m == p_clip) {
			delete m;
			m = nullptr;
			m_musicClips.erase(m_musicClips.begin() + 1); // delete from vector

			break;
		}
	}
}
