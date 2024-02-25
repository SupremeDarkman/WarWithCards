#include "App.h"
#include "Player.h"
#include <iostream>

const unsigned CARD_DEALED = 10;

App::App()
{
}

App::App(Player& player1, Player& player2, Player& player3)
	:backCardTexture(nullptr), card1Texture(nullptr), card2Texture(nullptr), card3Texture(nullptr), card4Texture(nullptr),
	card5Texture(nullptr), card6Texture(nullptr), card7Texture(nullptr), card8Texture(nullptr), card9Texture(nullptr),
	card10Texture(nullptr)

{
	window = NULL;
	renderer = NULL;
	running = true;
}

App::~App()
{

}

bool App::init(const std::string title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
	if (nullptr == window)
	{
		std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (nullptr == renderer)
	{
		std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
		return false;

	}
	SDL_Texture* card2ClubsTexture1 = loadTexture("assets/cards/backCard_120.png", renderer);
	if (!card2ClubsTexture1)
		return false;

	SDL_Surface* tempSurface = getSurface("assets/cards/backCard_120.png");
	card1Texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_SetTextureAlphaMod(card1Texture, 0);

	SDL_QueryTexture(card2ClubsTexture1, 0, 0, &tw, &th);

	dRectCard1 = { 0,150, tw, th };
	dRectCard2 = { 0,152, tw, th };
	dRectCard3 = { 0,154, tw, th };
	dRectCard4 = { 0,156, tw, th };
	dRectCard5 = { 0,158, tw, th };
	dRectCard6 = { 0,160, tw, th };
	dRectCard7 = { 0,162, tw, th };
	dRectCard8 = { 0,164, tw, th };
	dRectCard9 = { 0,166, tw, th };
	dRectCard10 = { 0,168, tw, th };

	SDL_FreeSurface(tempSurface);
	return true;
}

bool App::ttf_init()
{
	if (TTF_Init() == -1)
		return false;

	TTF_Font* font1 = TTF_OpenFont("assets/fonts/Arcade.ttf", 25);

	if (nullptr == font1)
		return false;

	SDL_Surface* tempSurfaceText = nullptr;

	tempSurfaceText = TTF_RenderText_Blended(font1, "Start", { 0x00, 0x00, 0x00, 0xFF });
	textStartTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "Deal", { 0x00, 0x00, 0x00, 0xFF });
	textDealTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	SDL_QueryTexture(textStartTexture, 0, 0, &tw, &th);
	dRectTextStart = { 5, 355, tw , th };

	SDL_QueryTexture(textDealTexture, 0, 0, &tw, &th);
	dRectTextDeal = { 95, 355, tw , th };

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font1);

	return true;
}

SDL_Surface* App::getSurface(const std::string filePath)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (nullptr == surface)
	{
		std::cerr << "Failed to load image: " << filePath << ": " << SDL_GetError() << std::endl;
		return nullptr;
	}
	return surface;
}

bool App::isClickableRectClicked(SDL_Rect* r, int xDown, int yDown, int xUp, int yUp)
{
	if ((xDown >= r->x && xDown <= (r->x + r->w) && xUp >= r->x && xUp <= (r->x + r->w) &&
		(yDown >= r->y && yDown <= (r->y + r->h) && yUp >= r->y && yUp <= (r->y + r->h))))
	{
		return true;
	}
	return false;
}

SDL_Texture* App::loadTexture(const std::string filePath, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = getSurface(filePath.c_str());

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
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard4);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard5);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard6);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard7);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard8);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard9);
	SDL_RenderCopy(renderer, card1Texture, nullptr, &dRectCard10);

	dRectButtonStart = { 0, 350, 70, 30 };
	dRectButtonDeal = { 80, 350, 70, 30 };
	SDL_SetRenderDrawColor(renderer, 0x00, 0xCA, 0xAC, 0xFF);
	SDL_RenderFillRect(renderer, &dRectButtonStart);
	SDL_RenderFillRect(renderer, &dRectButtonDeal);

	SDL_RenderCopy(renderer, textStartTexture, nullptr, &dRectTextStart);
	SDL_RenderCopy(renderer, textDealTexture, nullptr, &dRectTextDeal);


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
		case SDL_MOUSEBUTTONDOWN:
		{
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				mouseDownX = msx;
				mouseDownY = msy;
			}
		}; break;
		case SDL_MOUSEBUTTONUP:
		{
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				if (isClickableRectClicked(&dRectButtonStart, mouseDownX, mouseDownY, msx, msy))
				{
					std::cout << " CLICKED START";
					SDL_SetTextureAlphaMod(card1Texture, 255);
				}
				else if (isClickableRectClicked(&dRectButtonDeal, mouseDownX, mouseDownY, msx, msy))
				{
					std::cout << " CLICKED DEAL";
				}
				else
				{
					std::cout << " NOT CLICKED ";
				}
			}

		}; break;
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