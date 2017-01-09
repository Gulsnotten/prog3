#pragma once
#include <vector>

class MusicClip;
class Ghost;

enum Song {Siren, Fleeing, Dead, Not_Started};

class GhostSoundPicker
{
private:
	MusicClip* m_sirenwPtr;
	MusicClip* m_fleeingwPtr;
	MusicClip* m_deadwPtr;

	std::vector<Ghost*> m_ghostwPtr;
	Song m_currentSong;
public:
	GhostSoundPicker();
	GhostSoundPicker(std::vector<Ghost*> p_ghosts);
	~GhostSoundPicker();

	void AddGhost(Ghost* p_ghost);

	void PickSong();
	void StopSongs();
};