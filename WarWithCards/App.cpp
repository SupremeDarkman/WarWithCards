#include "App.h"
#include <iostream>

const unsigned CARD_DEALED = 10;

App::App(const std::vector<Player>& pl)
	:backCardTexture(nullptr), card1Texture(nullptr), card2Texture(nullptr), card3Texture(nullptr), card4Texture(nullptr),
	card5Texture(nullptr), card6Texture(nullptr), card7Texture(nullptr), card8Texture(nullptr), card9Texture(nullptr),
	card10Texture(nullptr)

{
	players = pl;
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
	SDL_SetRenderDrawColor(renderer, 0x00, 0xCA, 0xAC, 0xFF);
	SDL_Texture* backgroundTex = loadTexture("assets/cards/background.jpg", renderer);
	if (!backgroundTex) return false;
	SDL_Surface* tempSurface = getSurface("assets/cards/background.jpg");
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	dRectBackground = { 0,0,w,h };
	SDL_Texture* backCardTexture = loadTexture("assets/cards/backCard_120.png", renderer);
	if (!backCardTexture)
		return false;

	tempSurface = getSurface("assets/cards/backCard_120.png");
	card1Texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_SetTextureAlphaMod(card1Texture, 0);

	SDL_QueryTexture(backCardTexture, 0, 0, &tw, &th);

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
	TTF_Font* font2 = TTF_OpenFont("assets/fonts/segoepr.ttf", 45);
	TTF_Font* fontPlayer = TTF_OpenFont("assets/fonts/segoepr.ttf", 30);


	if (nullptr == font1 || nullptr == font2 || nullptr == fontPlayer)
		return false;

	SDL_Surface* tempSurfaceText = nullptr;

	tempSurfaceText = TTF_RenderText_Blended(font1, "Start", { 0x00, 0x00, 0x00, 0xFF });
	textStartTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "Deal", { 0x00, 0x00, 0x00, 0xFF });
	textDealTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Cannot Click", { 0x00, 0x00, 0x00, 0xFF });
	textErrorTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(fontPlayer, "Player 1", { 0x00,0x00,0x00,0xFF });
	textPlayer1Texture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	SDL_QueryTexture(textStartTexture, 0, 0, &tw, &th);
	dRectTextStart = { 5, 355, tw , th };

	SDL_QueryTexture(textDealTexture, 0, 0, &tw, &th);
	dRectTextDeal = { 95, 355, tw , th };

	SDL_QueryTexture(textErrorTexture, 0, 0, &tw, &th);
	dRectTextError = { 300, 50, tw, th };

	SDL_QueryTexture(textPlayer1Texture, 0, 0, &tw, &th);
	dRectTextPlayer1 = { 0, 100, tw, th };

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
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, nullptr, &dRectBackground);

	//SDL_QueryTexture(card.texture, 0, 0, &tw, &th);
	//drawTexture(card.texture, 200, 200, tw, th, SDL_FLIP_NONE); // where to go on the screen

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
	SDL_RenderFillRect(renderer, &dRectButtonStart);
	SDL_RenderFillRect(renderer, &dRectButtonDeal);

	SDL_RenderCopy(renderer, textStartTexture, nullptr, &dRectTextStart);
	SDL_RenderCopy(renderer, textDealTexture, nullptr, &dRectTextDeal);
	SDL_RenderCopy(renderer, textPlayer1Texture, nullptr, &dRectTextPlayer1);


	SDL_RenderPresent(renderer);
}
void App::loadTextureOnDeck(Deck& deck)
{
	const char* const arrSuit[4] = { "spades", "hearts", "diamonds", "clubs" };
	const char* const arrFace[13] = { "2", "3", "4", "5", "6" , "7" , "8" , "9" , "10" , "11" , "12" , "13", "14" };
	for (int i = 0; i < deck.getDeck().size(); i++)
	{
		std::string filePathRoot = "assets/cards/";
		filePathRoot.append(arrFace[i % 13]).append("_of_").append(arrSuit[i % 4]).append(".png");
		SDL_Texture* tex = loadTexture(filePathRoot, renderer);
		deck.getDeck()[i].texture = tex;
		if (!deck.getDeck()[i].texture)
			std::cerr << "Failed to load texture for card " << SDL_GetError() << std::endl;
	}
}

void App::drawTexture(SDL_Texture* tex, int x, int y, int width, int heigth, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0, 0, width, heigth }; // coord from the texture
	SDL_Rect dstRect = { x,y, width, heigth };
	SDL_RenderCopyEx(renderer, tex, &srcRect, &dstRect, 0, 0, flip);
}

SDL_Renderer* App::getRenderer()
{
	return renderer;
}

void App::handleEvents(Deck& deck)
{
	SDL_Event event;
	static bool wasPressed = false;
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
					if (wasPressed)
					{
						std::cout << "cannot click again";
						SDL_SetTextureAlphaMod(textErrorTexture, 255);
						SDL_RenderCopy(renderer, textErrorTexture, nullptr, &dRectTextError);
						SDL_RenderPresent(renderer);
						SDL_Delay(1000);
						SDL_SetTextureAlphaMod(textErrorTexture, 0);
					}
					else
					{
						wasPressed = true;
						std::cout << " CLICKED START";
						for (unsigned i = 0; i < players.size(); i++)
						{
							players[i].dealCards(deck);
						}

						SDL_SetTextureAlphaMod(textStartTexture, 128);
						SDL_SetTextureAlphaMod(card1Texture, 255);
					}
				}
				else if (isClickableRectClicked(&dRectButtonDeal, mouseDownX, mouseDownY, msx, msy))
				{
					std::cout << " CLICKED DEAL";
					Card c = players[0].pullCard();
					SDL_QueryTexture(c.texture, 0, 0, &tw, &th);

					drawTexture(c.texture, 200, 250, tw, th, SDL_FLIP_NONE);
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
	IMG_Quit();
	SDL_Quit();
}

bool App::isRunning()
{
	return running;
}
