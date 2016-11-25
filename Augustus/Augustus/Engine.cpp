#pragma once

#include "stdafx.h" // SDL
#include "Engine.h"
#include "DrawManager.h"

Engine::Engine() : m_drawManager(nullptr), m_spriteManager(nullptr),
					m_stateManager(nullptr), m_inputManager(nullptr),
					m_running(true)
{

}

Engine::~Engine()
{

}

void Engine::Initialize()
{
	m_drawManager = new DrawManager();
	m_drawManager->Initialize();
}

void Engine::Shutdown()
{
	m_drawManager->Shutdown();
}

void Engine::Run()
{
	while (m_running) {
		m_drawManager->SetDrawColor(0, 0, 0, 0);
		m_drawManager->Clear();
		m_drawManager->SetDrawColor(255, 0, 0, 0);
		m_drawManager->DebugDraw(100, 100, 100, 100);
		m_drawManager->Present();

		SDL_Delay(10);
	}
}

void Engine::HandleEvents()
{
}

void Engine::CalculateDeltatime()
{
}
