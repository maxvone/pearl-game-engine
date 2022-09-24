#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>

Game::Game()
{
	isRunning = false;
	std::cout << "Game constructor call" << std::endl;
}

Game::~Game()
{
	std::cout << "Game destructor call" << std::endl;
}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}

	//Struct for getting information about a monitor.
	//SDL_DisplayMode displayMode;
	//SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 800;
	windowHeight = 600;

	window = SDL_CreateWindow(NULL,	SDL_WINDOWPOS_CENTERED,	SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		std::cerr << "Error creating sdl window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		std::cerr << "Error creating sdl renderer." << std::endl;
		return;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}

void Game::Run()
{
	SetupGameLoop();
	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::SetupGameLoop()
{
	playerPosition = glm::vec2(10.0, 20.0);
	playerVelocity = glm::vec2(1.0, 0.0);
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
				}
				break;
		}
	}
}

void Game::Update()
{
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), millisecsPreviousFrame + MILISECS_PER_FRAME));

	millisecsPreviousFrame = SDL_GetTicks();

	playerPosition += playerVelocity;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* surface = IMG_Load("./assets/images/tree.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect destinationRect = {
		static_cast<int>(playerPosition.x),
		static_cast<int>(playerPosition.y),
		32, 32};

	SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
