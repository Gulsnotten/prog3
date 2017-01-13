#include "stdafx.h"
#include "Engine.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "ServiceLocator.h"
#include <iostream>

#include "PacmanGame.h"
#include "FPS_Helper.h"

#include <random>
#include <time.h>


Engine::Engine()
	: m_drawManager(nullptr), m_spriteManager(nullptr),
	m_stateManager(nullptr), m_inputManager(nullptr),
	m_running(true), m_lastTick(0)
{
	assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "SDL_Init Failed");
	assert(Mix_Init(MIX_INIT_OGG) != 0 && "Mix_Init Failed");
	assert(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != -1 && "Mix_OpenAudio Failed");
	assert(IMG_Init(IMG_INIT_PNG) != 0 && "IMG_Init Failed");
};

Engine::~Engine()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
};

void Engine::Initialize()
{
	m_drawManager = new DrawManager();
	m_drawManager->Initialize();
	m_spriteManager = new SpriteManager(m_drawManager->GetRenderer());
	m_stateManager = new StateManager();
	m_inputManager = new InputManager();
	m_inputManager->Initialize();
	m_soundManager = new SoundManager();
	m_soundManager->Initialize();


	ServiceLocator<DrawManager>::SetService(m_drawManager);
	ServiceLocator<SpriteManager>::SetService(m_spriteManager);
	ServiceLocator<InputManager>::SetService(m_inputManager);
	ServiceLocator<SoundManager>::SetService(m_soundManager);
	srand(int(time(0)));

	m_game = new PacmanGame();
	m_game->Enter();
};

void Engine::Shutdown()
{
	m_inputManager->Shutdown();
	delete m_inputManager;
	m_inputManager = nullptr;

	delete m_stateManager;
	m_stateManager = nullptr;

	delete m_spriteManager;
	m_spriteManager = nullptr;

	m_drawManager->Shutdown();
	delete m_drawManager;
	m_drawManager = nullptr;

	m_soundManager->Shutdown();
	delete m_soundManager;
	m_soundManager = nullptr;

	m_game->Exit();
	delete m_game;
	m_game = nullptr;
};

void Engine::Run()
{
	while (m_running)
	{
		m_drawManager->SetDrawColor(0, 0, 0, 255);
		m_drawManager->Clear();
		CalculateDeltatime();
		HandleEvents();

		if (!m_game->Update(m_delta))
			m_running = false;
		m_game->Draw();

		m_inputManager->Update();
		m_drawManager->Present();

		m_FPShelper.Update(m_delta);
	}
}


void Engine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT)
		{
			m_running = false;
		}
		else if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				m_drawManager->UpdateWindowSize();
			}
		}
		else
		{
			m_inputManager->HandleEvent(event);
		}
	}
}

void Engine::CalculateDeltatime()
{
	m_delta = 0.001f * (SDL_GetTicks() - m_lastTick);
	m_lastTick = SDL_GetTicks();

	// SOME LAG OF SORTS!!! (example, unfocused window etc., pressed in the console...)
	if (m_delta > 20 * 0.001f) {
		m_delta = 0;
	}
}