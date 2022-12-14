#include "Game.h"

Game::Game()
{
	isRunning = false;
	isFramerateLocked = false;
	Logger::Log("Game constructor call");
}

Game::~Game()
{
	Logger::Log("Game destructor call");
}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::Err("Error initializing SDL.");
		return;
	}

	SetupWindow();
	SetupRenderer();

	isRunning = true;
}

void Game::SetupWindow()
{
	windowWidth = 800;
	windowHeight = 600;

	window = SDL_CreateWindow(NULL,	SDL_WINDOWPOS_CENTERED,	SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		Logger::Err("Error creating sdl window.");
		return;
	}

	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Game::SetupRenderer()
{
	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		Logger::Err("Error creating sdl renderer");
		return;
	}
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
	playerVelocity = glm::vec2(100.0, 0.0);
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
	if (isFramerateLocked)
	{
		int millisecsToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
		if (millisecsToWait > 0 && millisecsToWait <= MILLISECS_PER_FRAME)
		{
			SDL_Delay(millisecsToWait);
		}
	}

	deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
	millisecsPreviousFrame = SDL_GetTicks();

	playerPosition += playerVelocity * deltaTime;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* surface = IMG_Load("./assets/images/truck-ford-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect destinationRect = {
		static_cast<int>(playerPosition.x),
		static_cast<int>(playerPosition.y),
		256, 256};

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
