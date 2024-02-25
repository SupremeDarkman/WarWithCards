#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
class Player;

class App
{
public:
	App();
	App(Player& player1, Player& player2, Player& player3);
	~App();

	static App& getInstance()
	{
		static App instance;
		return instance;
	}

	bool init(const std::string title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();
	void render();
	SDL_Renderer* getRenderer();
	SDL_Texture* loadTexture(const std::string filePath, SDL_Renderer* renderer);
	SDL_Surface* getSurface(const std::string filePath);
	bool isClickableRectClicked(SDL_Rect* r, int xDown, int yDown, int xUp, int yUp);

	void update();
	void handleEvents();
	void DestroySDL();
	bool isRunning();
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running;

	SDL_Texture* card1Texture, * card2Texture, * card3Texture, * card4Texture, * card5Texture, * card6Texture, * card7Texture,
		* card8Texture, * card9Texture, * card10Texture, * backCardTexture;
	SDL_Texture* textStartTexture, * textDealTexture;
	SDL_Rect dRectCard1 = {}, dRectCard2, dRectCard3, dRectCard4, dRectCard5, dRectCard6, dRectCard7, dRectCard8, dRectCard9, dRectCard10;
	SDL_Rect dRectButtonStart, dRectButtonDeal, dRectTextStart, dRectTextDeal;
	int mouseDownX, mouseDownY;
	int tw, th;
};