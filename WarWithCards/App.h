#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Player.h"

class App
{
public:
	App(const std::vector<Player>& players);
	~App();


	bool init(const std::string title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();
	void render();
	void loadTextureOnDeck(Deck& deck);
	void drawTexture(SDL_Texture* tex, int x, int y, int width, int heigth, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Renderer* getRenderer();
	SDL_Texture* loadTexture(const std::string filePath, SDL_Renderer* renderer);
	SDL_Surface* getSurface(const std::string filePath);
	bool isClickableRectClicked(SDL_Rect* r, int xDown, int yDown, int xUp, int yUp);

	void update();
	void handleEvents(Deck& deck);
	void DestroySDL();
	bool isRunning();
private:
	std::vector<Player> players;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running;

	SDL_Texture* card1Texture, * card2Texture, * card3Texture, * card4Texture, * card5Texture, * card6Texture, * card7Texture,
			* card8Texture, * card9Texture, * card10Texture, * backCardTexture, * backgroundTexture;
	SDL_Texture* textStartTexture, * textDealTexture, * textErrorTexture, * textPlayer1Texture;
	SDL_Rect dRectCard1 = {}, dRectCard2, dRectCard3, dRectCard4, dRectCard5, dRectCard6, dRectCard7, dRectCard8, dRectCard9, dRectCard10;
	SDL_Rect dRectButtonStart, dRectButtonDeal, dRectTextStart, dRectTextDeal, dRectBackground, dRectTextError, dRectTextPlayer1;
	int mouseDownX, mouseDownY;
	int tw, th;
};
