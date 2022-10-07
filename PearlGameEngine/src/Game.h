#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
	bool isFramerateLocked;
	int millisecsPreviousFrame = 0;
	float deltaTime;

	void SetupWindow();
	void SetupRenderer();
public:
	Game();
	~Game();

	void Initialize();
	void Run();
	void SetupGameLoop();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	int windowWidth;
	int windowHeight;
};

#endif
