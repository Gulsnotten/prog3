#pragma once

#include <string>

namespace Config {
	
	static const std::string
		POWER_UP_MSG = "POWER_UP";
	static const int
		MOVEMENT_SPEED = 8,
		MOVEMENT_SPEED_SLOW = 4,
		MOVEMENT_SPEED_FAST = 16,
		SPAWN_TIME = 15,
		FLEEING_TIME = 4,
		WARNING_TIME = 2,
		ANIMATION_SPEED_PACMAN = 50,
		ANIMATION_SPEED_PACMAN_DEATH = 150,
		ANIMATION_SPEED_GHOST = 150,
		SPRITE_SIZE = 16,
		TILE_SIZE = 8,
		WIN_FLASH_SPEED = 250
		;
	static const float
		PAUSE_TIME = 1.0f,
		WIN_PAUSE_TIME = 1.0f,
		WIN_ANIMATION_LENGTH = 2.0f
		;
}