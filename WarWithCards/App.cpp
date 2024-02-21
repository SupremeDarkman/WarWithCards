#include "App.h"
#include "Player.h"
#include <iostream>

bool App::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (nullptr == window)
	{
		std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (nullptr == renderer)
	{
		std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
		return false;

	}
	SDL_Texture* card2ClubsTexture1 = loadTexture("assets/cards/backCard_120.png", renderer);
	if (!card2ClubsTexture1)
		return false;

	SDL_Surface* tempSurface = getSurface("assets/cards/backCard_120.png");
	card1Texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_QueryTexture(card2ClubsTexture1, 0, 0, &tw, &th);
	dRectCard1 = { 0,150, tw, th };

	card2Texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_QueryTexture(card2ClubsTexture1, 0, 0, &tw, &th);
	dRectCard2 = { 0,152, tw, th };

	card2Texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_QueryTexture(card2ClubsTexture1, 0, 0, &tw, &th);
	dRectCard3 = { 0,154, tw, th };

	SDL_FreeSurface(tempSurface);
	return true;
}

bool App::ttf_init()
{
	if (TTF_Init() == -1)
		return false;

	TTF_Font* font1 = TTF_OpenFont("assets/fonts/Arcade.ttf", 50);

	if (nullptr == font1)
		return false;

	SDL_Surface* tempSurfaceText = nullptr;

	tempSurfaceText = TTF_RenderText_Blended(font1, "Start", { 0x00, 0x00, 0x00, 0xFF });
	textStartTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	//int tw, th;

	SDL_QueryTexture(textStartTexture, 0, 0, &tw, &th);
	dRectTextStart = { 10, 10, tw, th };

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font1);

	return true;
}

SDL_Surface* App::getSurface(const std::string& filePath)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (nullptr == surface)
	{
		std::cerr << "Failed to load image: " << filePath << ": " << SDL_GetError() << std::endl;
		return nullptr;
	}
	return surface;
}

SDL_Texture* App::loadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = getSurface(filePath);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}

void App::render()
{
	SDL_SetRenderDrawColor(renderer, 0xBB, 0xAA, 0xDD, 0xFF);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard1);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard2);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard3);

	dRectButtonStart = { 0, 350, 75, 50 };
	dRectButtonDeal = { 80, 350, 75, 50 };
	SDL_SetRenderDrawColor(renderer, 0x00, 0xCA, 0xAC, 0xFF);
	SDL_RenderFillRect(renderer, &dRectButtonStart);
	SDL_RenderFillRect(renderer, &dRectButtonDeal);

	SDL_RenderCopy(renderer, textStartTexture, nullptr, &dRectTextStart);


	SDL_RenderPresent(renderer);
}

SDL_Renderer* App::getRenderer()
{
	return renderer;
}

void App::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: running = false; break;
		default: break;
		}
	}
}

void App::update()
{
}

void App::DestroySDL()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool App::isRunning()
{
	return running;
}

App::App()
{
	window = NULL;
	renderer = NULL;
	running = true;
	currentFrame = 0;
}

App::~App()
{
	delete renderer;
	delete window;
}