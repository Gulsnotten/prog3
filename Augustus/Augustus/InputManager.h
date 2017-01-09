#pragma once
class Mouse;
class Keyboard;

class InputManager
{
public:
	InputManager();
	~InputManager();
	void Initialize();
	void Shutdown();
	SDL_Point GetMousePosition();
	SDL_Point GetMouseMotion();
	bool IsMouseButtonDown(int p_button);
	bool IsMouseButtonPressed(int p_button);
	bool IsMouseButtonReleased(int p_button);
	bool IsKeyDown(SDL_Scancode p_key);
	bool IsKeyDownOnce(SDL_Scancode p_key);
	void HandleEvent(SDL_Event &event);
	void Update();
private:
	Mouse* m_mouse;
	Keyboard* m_keyboard;
};

