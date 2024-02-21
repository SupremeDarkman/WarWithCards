#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
class App
{
public:
	App();
	~App();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();
	void render();
	SDL_Renderer* getRenderer();
	SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer);
	SDL_Surface* getSurface(const std::string& filePath);
	void update();
	void handleEvents();
	void DestroySDL();
	bool isRunning();
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running;
	int currentFrame;

	SDL_Texture* card1Texture, * card2Texture, * card3Texture, * backCardTexture, * textStartTexture, * textDealTexture;
	SDL_Rect dRectCard1, dRectCard2, dRectCard3, dRectBackCard, dRectButtonStart, dRectButtonDeal, dRectTextStart, dRectTextTexture;
	int mouseDownX, mouseDownY;
	int tw, th;
};