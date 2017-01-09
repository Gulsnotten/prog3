#include "stdafx.h"
#include "GhostSoundPicker.h"

#include "Ghost.h"
#include "SoundManager.h"
#include "ServiceLocator.h"

GhostSoundPicker::GhostSoundPicker()
{
}

GhostSoundPicker::GhostSoundPicker(std::vector<Ghost*> p_ghosts)
{
	m_ghostwPtr = p_ghosts;

	SoundManager* soundManager = ServiceLocator<SoundManager>::GetService();
	m_sirenwPtr = soundManager->CreateMusic("../Assets/sound/siren.wav");
	m_fleeingwPtr = soundManager->CreateMusic("../Assets/sound/fleeing.wav");
	m_deadwPtr = soundManager->CreateMusic("../Assets/sound/run_to_house.wav");

	m_currentSong = Song::Not_Started;
}

GhostSoundPicker::~GhostSoundPicker()
{
	StopSongs();
}

void GhostSoundPicker::AddGhost(Ghost * p_ghost)
{
	m_ghostwPtr.push_back(p_ghost);
}

void GhostSoundPicker::PickSong()
{
	bool fleeing = false;
	bool dead = false;

	for (auto g : m_ghostwPtr) {
		if (g->IsFleeing())
			fleeing = true;
		if (g->IsDead())
			dead = true;
	}

	if (dead) {
		if (m_currentSong != Song::Dead) {
			m_deadwPtr->PlayLooped();
		}
		m_currentSong = Song::Dead;
	}
	else if (fleeing) {
		if (m_currentSong != Song::Fleeing) {
			m_fleeingwPtr->PlayLooped();
		}
		m_currentSong = Song::Fleeing;
	}
	else {
		if (m_currentSong != Song::Siren) {
			m_sirenwPtr->PlayLooped();
		}
		m_currentSong = Song::Siren;
	}
}

void GhostSoundPicker::StopSongs()
{
	m_deadwPtr->Stop();
	m_fleeingwPtr->Stop();
	m_sirenwPtr->Stop();
}
